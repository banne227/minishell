/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:56:28 by banne             #+#    #+#             */
/*   Updated: 2026/01/08 15:31:26 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_limiter_and_active_heredoc(t_cmd *cmd)
{
	t_token	*current;
	char	*limiter;

	limiter = NULL;
	current = cmd->redir;
	while (current)
	{
		if (current->type == T_HEREDOC && current->str)
			limiter = current->str;
		current = current->next;
	}
	if (limiter)
		active_heredoc(limiter);
}

void	need_heredoc(t_cmd *cmd)
{
	int		found;
	t_token	*current;

	current = cmd->redir;
	found = 0;
	while (current)
	{
		if (current->type == T_HEREDOC && current->str)
			found += 1;
		current = current->next;
	}
	if (found > 0)
		find_limiter_and_active_heredoc(cmd);
	return ;
}

void	consume_all_heredocs(t_cmd *cmd)
{
	while (cmd)
	{
		need_heredoc(cmd);
		cmd = cmd->next;
	}
}

void	active_heredoc(char *limiter)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			free(line);
			print_warning(limiter);
			break ;
		}
		else if (strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		if (line)
			free(line);
	}
}
