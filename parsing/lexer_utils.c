/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:15:00 by banne             #+#    #+#             */
/*   Updated: 2026/01/07 16:34:49 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_spaces(char *s, int i)
{
	while (s[i] && is_isspace(s[i]))
		i++;
	return (i);
}

int	skip_quotes(const char *str, int i)
{
	char	quote;

	quote = str[i];
	if (quote != '\'' && quote != '"')
		return (i);
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

int	skip_redirs(char *s, int i)
{
	while (s[i] && is_redirection(s[i]))
		i++;
	return (i);
}

int	skip_word(char *s, int i)
{
	while (s[i] && !is_isspace(s[i]) && s[i] != '\'' && s[i] != '"')
		i++;
	return (i);
}
