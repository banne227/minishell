/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:45:00 by banne             #+#    #+#             */
/*   Updated: 2025/12/15 12:45:32 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env(t_env *env, const char *val)
{
	int		i;
	size_t	len;
	char	*result;

	result = NULL;
	if (!env || !env->envp || !val)
		return (ft_strdup(""));
	len = ft_strlen(val);
	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp(env->envp[i], val, len) == 0
			&& env->envp[i][len] == '=')
		{
			result = env->envp[i] + len + 1;
			return (ft_strdup(result));
		}
		i++;
	}
	return (ft_strdup(""));
}

char	**free_env(char **envp, int i)
{
	while (--i >= 0)
		free(envp[i]);
	free(envp);
	return (NULL);
}

char	**env_init(char **envp)
{
	char	**new_envp;
	int		i;
	int		size;

	size = 0;
	i = 0;
	while (envp[i])
		i++;
	size = i;
	new_envp = malloc(sizeof(char *) * (size + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
			return (free_env(new_envp, i));
		i++;
	}
	new_envp[size] = NULL;
	return (new_envp);
}
