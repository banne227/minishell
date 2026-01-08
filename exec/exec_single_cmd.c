/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:33:50 by banne             #+#    #+#             */
/*   Updated: 2026/01/08 14:04:53 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_child(t_cmd *cmd, t_data *data, t_token *tokens)
{
	(void)tokens;
	apply_redirections_to_cmd(cmd, data);
	do_redirections(cmd);
	if (cmd->error)
		exit(1);
	exec_single_cmd(cmd, data->env->envp, data);
}

void	exec_single_cmd(t_cmd *cmd, char **envp, t_data *data)
{
	char	*path;

	if (cmd->error)
		exit(1);
	path = find_cmd(cmd, envp, data);
	if (!path)
	{
		data->last_exit_status = 127;
		exit(127);
	}
	if (execve(path, cmd->args, envp) == -1)
	{
		free(path);
		if (access(cmd->args[0], F_OK) == 0)
		{
			ft_fprintf("minishell: ", cmd->args[0], ": Permission denied\n");
			data->last_exit_status = 126;
			exit(126);
		}
		put_error(cmd, "execution failed\n");
		data->last_exit_status = 126;
		exit(126);
	}
	free(path);
}

bool	is_builtin_child(t_cmd *cmd)
{
	if (cmd == NULL)
		return (false);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (true);
	return (false);
}
