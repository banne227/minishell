/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:34:03 by banne             #+#    #+#             */
/*   Updated: 2025/12/09 16:13:03 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fill_here_doc(t_cmd *cmd, const char *limiter, int write_fd)
{
	char	*line;

	if (!limiter || write_fd < 0)
		return (put_error(cmd, "Invalid heredoc parameters\n"));
	(void)cmd;
	while (1)
	{
		//if (stop_signal())
		//	return (-1);
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, write_fd);
		ft_putstr_fd("\n", write_fd);
		free(line);
	}
	return (1);
}

int	create_heredoc(t_cmd *cmd, const char *limiter)
{
	int		hd[2];
	pid_t	pid;

	setup_heredoc_signals();
	if (cmd->infile != STDIN_FILENO)
		close(cmd->infile);
	if (pipe(hd) == -1)
		return (put_error(cmd, "Failed to create heredoc pipe\n"));
	pid = fork();
	if (pid == -1)
		return (put_error(cmd, "Failed to fork heredoc process\n"));
	if (pid == 0)
	{
		close(hd[0]);
		if (fill_here_doc(cmd, limiter, hd[1]) == -1)
			exit(1);
		close(hd[1]);
		exit(0);
	}
	else
		close(hd[1]);
	waitpid(pid, NULL, 0);
	cmd->infile = hd[0];
	return (cmd->infile);
}
