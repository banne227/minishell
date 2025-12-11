/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:37:10 by jhauvill          #+#    #+#             */
/*   Updated: 2025/12/11 15:21:28 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expand_var(char	*result, int *j, int var_len, int var_start, char *str)
{
	int		k;
	char	*env;
	char	var_name[var_len + 1];

	k = 0;
	ft_strlcpy(var_name, str + var_start, var_len + 1);
	env = getenv(var_name);
	if (env)
    {
		while (env[k])
		result[(*j)++] = env[k++];
	}
	return (var_len + 1);
}

char	*env_to_cmd(char *str, int *quote)
{
    int		i;
	int 	var_start;
	int		j;
    char	*result;
	int		var_len;
	
	j = 0;
	i = 0;
	result = malloc(ft_strlen(str) * 2 + 1); // buffer large
    if (!result)
        return NULL;
    while (str[i])
    {
        if (str[i] == '$' && (!quote || *quote != 1))
        {
			var_start = i + 1;
			var_len = 0;
			while (str[var_start + var_len] && (ft_isalnum(str[var_start + var_len])
				|| str[var_start + var_len] == '_'))
                var_len++;
            if (var_len > 0)
				i += expand_var(result, &j, var_len, var_start, str);
            else
                result[j++] = str[i++];
        }
        else
            result[j++] = str[i++];
    }
    result[j] = '\0';
    return result;
}

char	*expand(char *str)
{
    int		quote;
    char	*no_quotes;
    char	*result;

    quote = 0;
    no_quotes = remove_quotes(str, &quote);
    if (str[0] == '$' && quote == 1) // quote == 1 => quotes simples
        result = ft_strdup(no_quotes); // Pas d'expansion
    else
        result = env_to_cmd(no_quotes, &quote);
    free(no_quotes);
    return (result);
}
