/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:29:28 by banne             #+#    #+#             */
/*   Updated: 2025/12/18 18:57:21 by jhauvill         ###   ########.fr       */
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
