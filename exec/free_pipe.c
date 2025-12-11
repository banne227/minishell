/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:17:25 by banne             #+#    #+#             */
/*   Updated: 2025/12/11 08:09:16 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_all_pipes(int **pipe_fd, int nbr_pipes)
{
	int	i;

	if (!pipe_fd)
		return (0);
	i = 0;
	while (i < nbr_pipes)
	{
		if (pipe_fd[i])
			free(pipe_fd[i]);
		i++;
	}
	free(pipe_fd);
	return (0);
}
