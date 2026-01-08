/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:56:28 by banne             #+#    #+#             */
/*   Updated: 2025/12/22 16:56:36 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_limiter_and_active_heredoc(t_cmd *cmd)
{
	t_token	*current;
	char	*limiter;

	current = cmd->redir;
	while (current)
	{
		if (current->type == T_HEREDOC && current->str)
			limiter = current->str;
		current = current->next;
	}
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
	else if (!found && cmd->args && cmd->args[0])
		ft_fprintf("minishell: ", cmd->args[0], ": command not found\n");
	else if (!found)
		ft_putstr_fd("minishell : Invalid syntax\n", 2);
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
