/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:52:55 by jhauvill          #+#    #+#             */
/*   Updated: 2025/12/10 12:47:16 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	quote_len(char * str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	*remove_quotes(char *str, int *quote)
{
	int		i;
	int		j;
	int		count;
	char	*new_str;

	i = 0;
	j = 0;
	count = quote_len(str);
	new_str = malloc(sizeof(char) * (count + 1));
	if (!new_str)
		return (NULL);
	while(str[i])
	{
		if (str[i] == '"')
			i++;
		else if (str[i] == '\'')
		{
			i++;
			*quote = 1;
		}
		else
		{
			new_str[j] = str[i];
			j++;
			i++;
		}
	}
	new_str[i] = '\0';
	return (new_str);
}
