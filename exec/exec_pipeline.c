/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:33:46 by banne             #+#    #+#             */
/*   Updated: 2025/12/11 12:32:23 by banne            ###   ########.fr       */
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

void	exec_cmd_pipe(t_cmd *cmd, int **pipe_fd, int cmd_i, t_data *minishell)
{
	char	*path_cmd;

	if (have_redirections(cmd))
		apply_redirections_to_cmd(cmd, minishell->tokens);
	path_cmd = find_cmd(cmd, minishell->env->envp);
	if (path_cmd == NULL)
		exit(command_not_found(cmd));
	if (cmd->infile != STDIN_FILENO)
		dup2(cmd->infile, STDIN_FILENO);
	else if (cmd_i > 0)
		dup2(pipe_fd[cmd_i - 1][0], STDIN_FILENO);
	if (cmd->outfile != STDOUT_FILENO)
		dup2(cmd->outfile, STDOUT_FILENO);
	else if (cmd_i < minishell->cmd_count - 1)
		dup2(pipe_fd[cmd_i][1], STDOUT_FILENO);
	close_all_pipes(pipe_fd, minishell->cmd_count - 1, cmd);
	execve(path_cmd, cmd->args, minishell->env->envp);
	perror("execve cmd failed");
	exit(EXIT_FAILURE);
}

void	fork_and_exec(pid_t *pids, int **pipe_fd, t_data *minishell)
{
	int		i;
	t_cmd	*current_cmd;

	i = 0;
	current_cmd = minishell->cmds;
	while (i < minishell->cmd_count && current_cmd)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
			exec_cmd_pipe(current_cmd, pipe_fd, i, minishell);
		current_cmd = current_cmd->next;
		i++;
	}
}

void	pipe_execute(t_data *minishell)
{
	int		i;
	pid_t	*pids;
	int		**pipe_fd;

	pids = malloc(sizeof(pid_t) * minishell->cmd_count);
	if (!pids)
	{
		perror("malloc failed");
		return ;
	}
	pipe_fd = init_pipes(minishell->cmd_count);
	if (!pipe_fd)
		return ;
	i = 0;
	fork_and_exec(pids, pipe_fd, minishell);
	close_all_pipes(pipe_fd, minishell->cmd_count - 1, NULL);
	while (i < minishell->cmd_count)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	minishell->last_exit_status = 0;
	free_all_pipes(pipe_fd, minishell->cmd_count - 1);
	free(pids);
}

void	exec_pipeline(t_cmd *cmd, t_env *env, t_token *tokens)
{
	t_data	minishell;

	minishell.cmds = cmd;
	minishell.env = env;
	minishell.tokens = tokens;
	minishell.cmd_count = 0;
	while (minishell.cmds && minishell.cmds->args)
	{
		minishell.cmd_count++;
		minishell.cmds = minishell.cmds->next;
	}
	minishell.cmds = cmd;
	pipe_execute(&minishell);
}
