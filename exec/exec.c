/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:33:53 by banne             #+#    #+#             */
/*   Updated: 2026/01/08 15:43:32 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (false);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (true);
	return (false);
}

void	run_builtin(t_cmd *cmd, t_env *env, t_data *data)
{
	int	saved_stdin;
	int	saved_stdout;

	if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit(cmd->args, data);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	apply_redirections_to_cmd(cmd, data);
	do_redirections(cmd);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		data->last_exit_status = ft_cd(cmd->args, env);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		ft_export(cmd->args, env);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_unset(cmd->args, env);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		ft_env(cmd->args, env->envp);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

bool	verify_cmd(t_cmd *cmd, t_data *data)
{
	int		i;
	char	*path;
	bool	valid;
	t_cmd	*head;

	i = 0;
	valid = true;
	head = cmd;
	while (cmd != NULL && valid != false)
	{
		path = find_cmd(cmd, data->env->envp, data);
		if (!path && is_builtin(cmd) == false)
		{
			print_cmd_error(cmd, data);
			valid = false;
			break ;
		}
		free(path);
		cmd = cmd->next;
	}
	if (valid == false)
		consume_all_heredocs(head);
	return (valid);
}

void	exec_cmd(t_data *data)
{
	pid_t	pid;

	if (!data->cmds)
		return (data->last_exit_status = 2, put_void());
	if (!verify_cmd(data->cmds, data))
		return ;
	if (!data->cmds->args[0])
		return ;
	if (count_pipes(data->tokens) > 0)
		return (exec_pipeline(data->cmds, data->env, data->tokens, data));
	if (is_builtin(data->cmds))
		return (run_builtin(data->cmds, data->env, data));
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		exit_error(1, data);
	if (pid == 0)
	{
		setup_child_signals();
		exec_child(data->cmds, data, data->tokens);
	}
	else
		get_status(pid, data);
}
