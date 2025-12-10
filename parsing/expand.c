/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:37:10 by jhauvill          #+#    #+#             */
/*   Updated: 2025/12/10 12:50:13 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*env_to_cmd(char *str, int *quote)
{	
	char	*env;

	if (!str)
		return (NULL);
	env = getenv(str + 1);
	if (str[0] == '$' && !(*quote))
	{
		if (env)
			return (ft_strdup(env));
		else
			return (ft_strdup(""));
	}
	else
		return (ft_strdup(str));
}

char	*expand(char *str)
{
	int		quote;
	char	*new_str;
	
	quote = 0;
	new_str = env_to_cmd(remove_quotes(str, &quote), &quote);
	return (new_str);
}
