/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:00:01 by jhauvill          #+#    #+#             */
/*   Updated: 2026/01/07 16:45:40 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_args_cmd(char *cmd, int i)
{
	int		count;

	count = 0;
	while (cmd[i])
	{
		while (cmd[i] && is_isspace(cmd[i]))
			i++;
		if (!cmd[i])
			break ;
		count++;
		if (cmd[i] == '\'' || cmd[i] == '"')
			i = skip_quotes(cmd, i);
		else if (is_redirection(cmd[i]))
			while (is_redirection(cmd[i]))
				i++;
		else
			while (cmd[i] && !is_isspace(cmd[i])
				&& cmd[i] != '\'' && cmd[i] != '"')
				i++;
	}
	return (count);
}

static char	*get_array(char *cmd, int *i)
{
	int		start;
	char	*res;

	if (cmd[*i] == '\'' || cmd[*i] == '"')
	{
		start = *i;
		*i = skip_quotes(cmd, *i);
		res = ft_substr(cmd, start, *i - start);
		return (res);
	}
	else if (is_redirection(cmd[*i]))
	{
		start = *i;
		*i = skip_redirs(cmd, *i);
		res = ft_substr(cmd, start, *i - start);
		return (res);
	}
	else
	{
		start = *i;
		*i = skip_word(cmd, *i);
		res = ft_substr(cmd, start, *i - start);
		return (res);
	}
}

static char	**parsing_cmd(char *cmd)
{
	int		count;
	char	**cmd_array;
	int		i;
	int		arg_idx;
	int		start;

	if (!is_valid(cmd))
		return (NULL);
	count = count_args_cmd(cmd, 0);
	cmd_array = malloc(sizeof(char *) * (count + 1));
	if (!cmd_array)
		return (NULL);
	i = 0;
	arg_idx = 0;
	while (cmd[i])
	{
		while (cmd[i] && is_isspace(cmd[i]))
			i++;
		if (!cmd[i])
			break ;
		start = i;
		cmd_array[arg_idx++] = get_array(cmd, &i);
	}
	cmd_array[arg_idx] = NULL;
	return (cmd_array);
}

static void	not_stored_token(t_token *tokens, char **tab)
{
	int		j;
	bool	found;
	t_token	*cur;

	j = 0;
	while (tab[j])
	{
		found = false;
		cur = tokens;
		while (cur)
		{
			if (cur->str == tab[j])
			{
				found = true;
				break ;
			}
			cur = cur->next;
		}
		if (!found)
			free(tab[j]);
		j++;
	}
	free(tab);
}

t_token	*lexer(char *line)
{
	int		i;
	t_token	*tokens;
	char	**tab;

	tokens = NULL;
	tab = parsing_cmd(line);
	if (!tab || tab == NULL)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		if (is_pipe(tab[i], &tokens))
			i++;
		else if (tab[i + 1] && is_redir(tab[i], tab[i + 1], &tokens))
			i += 2;
		else if (is_cmd(tab[i], &tokens))
			i++;
		else
		{
			add_token(&tokens, tab[i], T_ARG);
			i++;
		}
	}
	not_stored_token(tokens, tab);
	return (tokens);
}
