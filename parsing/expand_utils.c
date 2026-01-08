/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:27:54 by jhauvill          #+#    #+#             */
/*   Updated: 2025/12/23 12:06:54 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	env_value_len(char *str, int start, int var_len, t_env *env)
{
	char	*var;
	char	*var_env;
	int		len;

	len = 0;
	var = malloc(var_len + 1);
	if (!var)
		return (0);
	ft_strlcpy(var, &str[start], var_len + 1);
	var_env = get_env(env, var);
	if (var_env)
		len = ft_strlen(var_env);
	free(var);
	free(var_env);
	return (len);
}

static int	classic_expand(char *str, int *i, t_env *env)
{
	int	len;
	int	var_len;

	len = 0;
	var_len = 0;
	var_len = get_var_len(&str[*i]);
	if (var_len > 0)
	{
		len += env_value_len(str, *i, var_len, env);
		(*i) += var_len;
	}
	return (len);
}

static void	iterate(int *i, int *len)
{
	(*i) += 1;
	(*len) += 1;
}

int	expand_len(char *str, int *quote, t_env *env, int len)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '$' && (!quote || *quote != 1))
		{
			i++;
			if (!str[i])
				len += 1;
			else if (str[i] == '?')
			{
				len += 3;
				i++;
			}
			else
				len += classic_expand(str, &i, env);
		}
		else
			iterate(&i, &len);
	}
	return (len);
}
