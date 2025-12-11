/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:52:55 by jhauvill          #+#    #+#             */
/*   Updated: 2025/12/11 15:21:43 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*remove_quotes(char *str, int *quote)
{
    int		i = 0, j = 0;
    int		count = 0;
    char	*new_str;
    char	quote_char = 0;

    while (str[i])
    {
        if ((str[i] == '"' || str[i] == '\'') && !quote_char)
        {
            quote_char = str[i];
            if (quote_char == '\'')
                *quote = 1;
            i++;
        }
        else if (str[i] == quote_char)
        {
            quote_char = 0;
            i++;
        }
        else
        {
            count++;
            i++;
        }
    }
    new_str = malloc(sizeof(char) * (count + 1));
    if (!new_str)
        return (NULL);

    i = 0;
    j = 0;
    quote_char = 0;
    while (str[i])
    {
        if ((str[i] == '"' || str[i] == '\'') && !quote_char)
            quote_char = str[i++];
        else if (str[i] == quote_char)
            quote_char = 0, i++;
        else
            new_str[j++] = str[i++];
    }
    new_str[j] = '\0';
    return (new_str);
}
