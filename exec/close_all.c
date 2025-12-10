/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:59:17 by banne             #+#    #+#             */
/*   Updated: 2025/12/09 12:34:47 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fds(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->infile != STDIN_FILENO)
		close(cmd->infile);
	if (cmd->outfile != STDOUT_FILENO)
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
			if (pipe_fd[i][0] >= 0)
				close(pipe_fd[i][0]);
			if (pipe_fd[i][1] >= 0)
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
