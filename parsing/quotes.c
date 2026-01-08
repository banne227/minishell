/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:52:55 by jhauvill          #+#    #+#             */
/*   Updated: 2026/01/07 16:21:36 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*char_without_quotes(char *str, char quote_char, int count)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote_char = 0;
	new_str = malloc(sizeof(char) * (count + 1));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !quote_char)
			quote_char = str[i];
		else if (str[i] == quote_char)
			quote_char = 0;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*remove_quotes(char *str, int *quote)
{
	int		i;
	int		count;
	char	quote_char;

	i = 0;
	count = 0;
	quote_char = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !quote_char)
		{
			quote_char = str[i];
			if (quote_char == '\'')
				*quote = 1;
		}
		else if (str[i] == quote_char)
			quote_char = 0;
		else
			count++;
		i++;
	}
	return (char_without_quotes(str, quote_char, count));
}
