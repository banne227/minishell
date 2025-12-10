/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:33:50 by banne             #+#    #+#             */
/*   Updated: 2025/12/09 14:03:55 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_child(t_cmd *cmd, t_env *env, t_token *tokens)
{
	setup_child_signals();
	apply_redirections_to_cmd(cmd, tokens);
	if (cmd->error)
		exit(1);
	exec_single_cmd(cmd, env->envp);
}

void	exec_single_cmd(t_cmd *cmd, char **envp)
{
	char	*path;

	if (cmd->error)
		exit(1);
	path = find_cmd(cmd, envp);
	if (!path)
		exit(127);
	if (execve(path, cmd->args, envp) == -1)
	{
		free(path);
		put_error(cmd, "execution failed\n");
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
	return (false);
}
