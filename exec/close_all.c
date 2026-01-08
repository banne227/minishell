/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:59:17 by banne             #+#    #+#             */
/*   Updated: 2026/01/08 14:52:36 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fds(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->infile != STDIN_FILENO && cmd->infile != -1)
		close(cmd->infile);
	if (cmd->outfile != STDOUT_FILENO && cmd->outfile != -1)
		close(cmd->outfile);
}

void	close_pipes_fds(int **pipe_fd, int nbr_pipes)
{
	int	i;

	i = 0;
	while (i < nbr_pipes)
	{
		if (pipe_fd[i])
		{
			if (pipe_fd[i][0] >= 0 && pipe_fd[i][0] != -1)
				close(pipe_fd[i][0]);
			if (pipe_fd[i][1] >= 0 && pipe_fd[i][1] != -1)
				close(pipe_fd[i][1]);
		}
		i++;
	}
}

void	close_all_pipes(int **pipe_fd, int nbr_pipes, t_cmd *cmd)
{
	if (!pipe_fd)
		return ;
	close_pipes_fds(pipe_fd, nbr_pipes);
	close_fds(cmd);
}
