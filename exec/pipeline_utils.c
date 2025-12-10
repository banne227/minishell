/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:29:28 by banne             #+#    #+#             */
/*   Updated: 2025/12/09 16:04:48 by banne            ###   ########.fr       */
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

int	command_not_found(t_cmd *cmd)
{
	fprintf(stderr, "minishell: %s: command not found\n", cmd->args[0]);
	cmd->error = true;
	if (cmd->infile != STDIN_FILENO)
		close(cmd->infile);
	if (cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
	return (127);
}

int	**pipe_error(int **pipe_fd, int nbr_pipes)
{
	perror("pipe failed");
	close_pipes_fds(pipe_fd, nbr_pipes);
	return (NULL);
}
