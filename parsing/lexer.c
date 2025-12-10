/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:00:01 by jhauvill          #+#    #+#             */
/*   Updated: 2025/12/10 13:55:44 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_args_cmd(char *cmd, int i)
{
	char	quote;
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
		{
			quote = cmd[i++];
			while (cmd[i] && cmd[i] != quote)
				i++;
			if (cmd[i] == quote)
				i++;
		}
		else
			while (cmd[i] && !is_isspace(cmd[i]))
				i++;
	}
	return (count);
}

static char	*get_array(char *cmd, int *i)
{
	char	quote;
	int		start;
	char	*res;

	if (cmd[*i] == '\'' || cmd[*i] == '"')
	{
		quote = cmd[(*i)];
		start = *i;
		(*i)++;
		while (cmd[*i] && cmd[*i] != quote)
			(*i)++;
		if (cmd[*i] == quote)
			(*i)++;
		res = ft_substr(cmd, start, *i - start);
		if (cmd[*i] == quote)
			(*i)++;
		return (res);
	}
	else
	{
		start = *i;
		while (cmd[*i] && !is_isspace(cmd[*i]))
			(*i)++;
		return (ft_substr(cmd, start, *i - start));
	}
}

static char	**parsing_cmd(char *cmd)
{
	int		count;
	char	**cmd_array;
	int		i;
	int		arg_idx;
	int		start;

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
	i = 0;
	//fprintf(stderr, "DEBUG parsing_cmd: ");
	while (cmd_array[i])
	{
		fprintf(stderr, "[%s] ", cmd_array[i]);
		i++;
	}
	fprintf(stderr, "\n");
	return (cmd_array);
}

//static void	debug_tokens(t_token *tokens)
//{
//	while (tokens)
//	{
//		fprintf(stderr, "[%d:%s] ", tokens->type, tokens->str ? tokens->str : "NULL");
//		tokens = tokens->next;
//	}
//	fprintf(stderr, "\n");
//}

t_token	*lexer(char *line)
{
	int		i;
	t_token	*tokens;
	char	**tab;
	int		is_first_cmd;

	tokens = NULL;
	tab = parsing_cmd(line);
	if (!tab)
		return (NULL);
	i = 0;
	is_first_cmd = 1;
	while (tab[i])
	{
		if (is_pipe(tab[i], &tokens))
			i++;
		else if (is_redir(tab[i], tab[i + 1], &tokens))
			i+= 2;
		else if (is_cmd(tab[i], &tokens))
			i++;
		else
		{
			add_token(&tokens, tab[i], T_ARG);
			i++;
		}
	}
	//debug_tokens(tokens);
	//free(tab);
	return (tokens);
}
