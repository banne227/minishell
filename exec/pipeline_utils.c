/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:29:28 by banne             #+#    #+#             */
/*   Updated: 2026/01/08 14:53:23 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	have_redirections(t_cmd *cmd)
{
	if (!cmd)
		return (false);
	if (cmd->infile != STDIN_FILENO || cmd->outfile != STDOUT_FILENO)
		return (true);
	return (false);
}

int	command_not_found(t_cmd *cmd, t_data *minishell)
{
	minishell->last_exit_status = 127;
	ft_fprintf("minishell: ", cmd->args[0], ": command not found\n");
	cmd->error = true;
	if (cmd->infile != STDIN_FILENO && cmd->infile != -1)
		close(cmd->infile);
	if (cmd->outfile != STDOUT_FILENO && cmd->outfile != -1)
		close(cmd->outfile);
	return (127);
}

int	**pipe_error(int **pipe_fd, int nbr_pipes)
{
	perror("pipe failed");
	close_pipes_fds(pipe_fd, nbr_pipes);
	return (NULL);
}
