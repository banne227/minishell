/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:33:46 by banne             #+#    #+#             */
/*   Updated: 2025/12/23 11:03:54 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	**init_pipes(int nbr_cmds)
{
	int	i;
	int	**pipe_fd;

	i = 0;
	pipe_fd = malloc(sizeof(int *) * (nbr_cmds - 1));
	if (!pipe_fd)
	{
		perror("malloc failed");
		return (NULL);
	}
	while (i < nbr_cmds - 1)
	{
		pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!pipe_fd[i])
			return (pipe_error(pipe_fd, nbr_cmds - 1));
		if (pipe(pipe_fd[i]) == -1)
			return (pipe_error(pipe_fd, nbr_cmds - 1));
		i++;
	}
	return (pipe_fd);
}

void	exec_cmd_pipe(t_cmd *cmd, int cmd_i, t_data *minishell, t_pipe *pipe)
{
	char	*path_cmd;

	apply_redirections_to_cmd(cmd, minishell);
	if (cmd->infile != STDIN_FILENO && cmd->infile != -1 && cmd_i == 0)
		dup2(cmd->infile, STDIN_FILENO);
	else if (cmd_i > 0)
		dup2(pipe->pipe_fd[cmd_i - 1][0], STDIN_FILENO);
	if (cmd->outfile != STDOUT_FILENO)
		dup2(cmd->outfile, STDOUT_FILENO);
	else if (cmd_i < minishell->cmd_count - 1)
		dup2(pipe->pipe_fd[cmd_i][1], STDOUT_FILENO);
	close_all_pipes(pipe->pipe_fd, minishell->cmd_count - 1, cmd);
	if (is_builtin(cmd))
		handel_builtin(cmd, pipe, minishell);
	path_cmd = find_cmd(cmd, minishell->env->envp, minishell);
	if (path_cmd == NULL)
		exit(command_not_found(cmd, minishell));
	execve(path_cmd, cmd->args, minishell->env->envp);
	perror("execve cmd failed");
	free(path_cmd);
	exit(EXIT_FAILURE);
}

void	fork_and_exec(t_pipe pipe_struct, t_data *minishell)
{
	int		i;
	t_cmd	*current_cmd;

	i = 0;
	current_cmd = minishell->cmds;
	while (i < minishell->cmd_count && current_cmd)
	{
		pipe_struct.pids[i] = fork();
		if (pipe_struct.pids[i] < 0)
		{
			perror("fork failed");
			minishell->last_exit_status = 1;
			exit(EXIT_FAILURE);
		}
		if (pipe_struct.pids[i] == 0)
			exec_cmd_pipe(current_cmd, i, minishell, &pipe_struct);
		current_cmd = current_cmd->next;
		i++;
	}
}

void	pipe_execute(t_data *minishell, t_data *data)
{
	int		i;
	t_pipe	pipe_struct;

	pipe_struct.pids = malloc(sizeof(pid_t) * minishell->cmd_count);
	if (!pipe_struct.pids)
	{
		perror("malloc failed");
		return ;
	}
	pipe_struct.pipe_fd = init_pipes(minishell->cmd_count);
	if (!pipe_struct.pipe_fd)
	{
		free(pipe_struct.pids);
		return ;
	}
	pipe_struct.orig_data = data;
	fork_and_exec(pipe_struct, minishell);
	close_all_pipes(pipe_struct.pipe_fd, minishell->cmd_count - 1, NULL);
	i = 0;
	while (i < minishell->cmd_count)
		get_status(pipe_struct.pids[i++], minishell);
	free_all_pipes(pipe_struct.pipe_fd, minishell->cmd_count - 1);
	if (pipe_struct.pids)
		free(pipe_struct.pids);
}

void	exec_pipeline(t_cmd *cmd, t_env *env, t_token *tokens, t_data *data)
{
	t_data	minishell;

	minishell.cmds = cmd;
	minishell.env = env;
	minishell.tokens = tokens;
	minishell.last_exit_status = data->last_exit_status;
	minishell.here_doc = 0;
	minishell.need_free = false;
	minishell.cmd_count = 0;
	while (minishell.cmds && minishell.cmds->args)
	{
		minishell.cmd_count++;
		minishell.cmds = minishell.cmds->next;
	}
	minishell.cmds = cmd;
	pipe_execute(&minishell, data);
}
