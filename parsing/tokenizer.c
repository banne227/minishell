/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:06:04 by jhauvill          #+#    #+#             */
/*   Updated: 2025/12/10 13:48:27 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*create_token(char *str, t_tokentype type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->str = str;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **tokens, char *str, t_tokentype type)
{
	t_token	*new_token;
	t_token	*tmp;

	new_token = create_token(str, type);
	if (!new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}

int	is_redir(char *line, char *next_line, t_token **tokens)
{
	int	i;

	i = 0;
	if (line[0] == '<')
	{
		if (line[1] == '<' && !line[2])
			add_token(tokens, next_line, T_HEREDOC);
		else if (!line[1])
			add_token(tokens, next_line, T_INPUT);
		i++;
	}
	if (line[0] == '>')
	{
		if (line[1] == '>' && !line[2])
			add_token(tokens, next_line, T_APPEND);
		else if (!line[1])
			add_token(tokens, next_line, T_TRUNC);
		i++;
	}
	return (i);
}

int	is_pipe(char *line, t_token **tokens)
{
	if (line[0] == '|' && !line[1])
		return (add_token(tokens, line, T_PIPE), 1);
	return (0);
}

int	is_cmd(char *line, t_token **tokens)
{
	if (ft_strcmp(line, "exit") == 0)
		return (add_token(tokens, line, T_CMD), 1);
	if (ft_strcmp(line, "cd") == 0)
		return (add_token(tokens, line, T_CMD), 1);
	if (ft_strcmp(line, "pwd") == 0)
		return (add_token(tokens, line, T_CMD), 1);
	if (ft_strcmp(line, "export") == 0)
		return (add_token(tokens, line, T_CMD), 1);
	if (ft_strcmp(line, "unset") == 0)
		return (add_token(tokens, line, T_CMD), 1);
	if (ft_strcmp(line, "env") == 0)
		return (add_token(tokens, line, T_CMD), 1);
	if (ft_strcmp(line, "echo") == 0)
		return (add_token(tokens, line, T_CMD), 1);
	return (0);
}
