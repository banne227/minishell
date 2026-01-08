/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:34:03 by banne             #+#    #+#             */
/*   Updated: 2026/01/08 14:53:01 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_warning(const char *limiter)
{
	ft_putstr_fd("warning: here-document delimited ", 2);
	ft_fprintf("by end-of-file (wanted ", (char *)limiter, ")\n");
}

int	fill(t_cmd *cmd, const char *limiter, int write_fd, t_data *data)
{
	char	*line;

	if (!limiter || write_fd < 0)
		return (put_error(cmd, "Invalid heredoc parameters\n"));
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			free(line);
			print_warning(limiter);
			break ;
		}
		if (strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		line = expand(line, data);
		ft_putstr_fd(line, write_fd);
		ft_putstr_fd("\n", write_fd);
		free(line);
	}
	return (1);
}

int	create_heredoc(t_cmd *cmd, const char *limiter, t_data *data)
{
	int		hd[2];
	pid_t	pid;

	setup_heredoc_signals();
	if (cmd->infile != STDIN_FILENO && cmd->infile != -1)
		close(cmd->infile);
	if (pipe(hd) == -1)
		return (put_error(cmd, "Failed to create heredoc pipe\n"));
	pid = fork();
	if (pid == -1)
		return (put_error(cmd, "Failed to fork heredoc process\n"));
	if (pid == 0)
	{
		close(hd[0]);
		if (fill(cmd, limiter, hd[1], data) == -1)
			exit_error(1, data);
		close(hd[1]);
		exit_error(0, data);
	}
	else
		close(hd[1]);
	waitpid(pid, NULL, 0);
	cmd->infile = hd[0];
	return (cmd->infile);
}
