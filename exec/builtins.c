/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 11:05:59 by banne             #+#    #+#             */
/*   Updated: 2026/01/08 14:28:52 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handel_builtin(t_cmd *cmd, t_pipe *pipe, t_data *minishell)
{
	int	is_exit;

	is_exit = (cmd->args[0] && ft_strcmp(cmd->args[0], "exit") == 0);
	if (is_exit)
	{
		free_all_pipes(pipe->pipe_fd, minishell->cmd_count - 1);
		if (pipe->pids)
			free(pipe->pids);
		apply_redirections_to_cmd(cmd, minishell);
		do_redirections(cmd);
		ft_exit(cmd->args, minishell);
		free_all_pipelines(*pipe, minishell->cmd_count - 1);
		if (cmd->infile != STDIN_FILENO && cmd->infile != -1)
			close(cmd->infile);
		if (cmd->outfile != STDOUT_FILENO && cmd->outfile != -1)
			close(cmd->outfile);
	}
	else
	{
		run_builtin(cmd, minishell->env, minishell);
		free_all_pipelines(*pipe, minishell->cmd_count - 1);
	}
	exit(0);
}
