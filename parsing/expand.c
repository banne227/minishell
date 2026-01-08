/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:37:10 by jhauvill          #+#    #+#             */
/*   Updated: 2025/12/23 12:07:05 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_var_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}

static	void	copy_env_value(t_expand *expand, char *var, t_env *env)
{
	char	*var_env;
	int		k;

	k = 0;
	var_env = get_env(env, var);
	if (!var_env)
		return ;
	while (var_env[k])
	{
		expand->result[expand->j++] = var_env[k++];
	}
	free(var_env);
}

static int	handle_dollar(char *str, t_expand *expand, t_data *data)
{
	int		var_len;
	char	*var;
	char	*exit_status;
	int		k;

	(expand->i)++;
	if (str[expand->i] == '?')
	{
		exit_status = ft_itoa(data->last_exit_status);
		k = 0;
		while (exit_status[k])
			expand->result[expand->j++] = exit_status[k++];
		(expand->i)++;
		return (free(exit_status), 0);
	}
	var_len = get_var_len(&str[expand->i]);
	if (var_len == 0)
		return (0);
	var = malloc(var_len + 1);
	if (!var)
		return (-1);
	ft_strlcpy(var, &str[expand->i], var_len + 1);
	copy_env_value(expand, var, data->env);
	expand->i += var_len;
	return (free(var), 0);
}

char	*env_to_cmd(char *str, int *quote, t_data *data)
{
	t_expand	expand;
	int			alloc_size;

	expand.j = 0;
	expand.i = 0;
	alloc_size = expand_len(str, quote, data->env, 0) + 1;
	expand.result = malloc(sizeof(char) * alloc_size);
	if (!expand.result)
		return (NULL);
	while (str && str[expand.i])
	{
		if (str[expand.i] == '$' && (!quote || *quote != 1)
			&& str[expand.i + 1])
		{
			if (handle_dollar(str, &expand, data) == -1)
			{
				free(expand.result);
				return (NULL);
			}
		}
		else
			expand.result[expand.j++] = str[expand.i++];
	}
	expand.result[expand.j] = '\0';
	return (expand.result);
}

char	*expand(char *str, t_data *data)
{
	int		quote;
	char	*no_quotes;
	char	*result;

	quote = 0;
	no_quotes = remove_quotes(str, &quote);
	if (str[0] == '$' && quote == 1)
		result = ft_strdup(no_quotes);
	else
		result = env_to_cmd(no_quotes, &quote, data);
	free(no_quotes);
	return (result);
}
