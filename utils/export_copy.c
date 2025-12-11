/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:15:02 by banne             #+#    #+#             */
/*   Updated: 2025/12/11 13:52:55 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_env(t_env *env, char **new_envp)
{
	int	i;

	i = 0;
	while (env->envp[i])
	{
		new_envp[i] = ft_strdup(env->envp[i]);
		i++;
	}
}

void	copy_update_env(t_env *env, char **copy, int size, t_export export)
{
	int		i;
	char	*new_var;

	i = 0;
	new_var = malloc(strlen(export.key) + 1 + strlen(export.value) + 1);
	if (!new_var)
		return ;
	write_env_var(new_var, export, strlen(export.key));
	while (i < size)
	{
		if (ft_strncmp(env->envp[i], export.key, strlen(export.key)) != 0
			|| env->envp[i][strlen(export.key)] != '=')
			copy[i] = ft_strdup(env->envp[i]);
		else
			copy[i] = new_var;
		i++;
	}
	copy[size] = NULL;
}

void	copy_remove_env(t_env *env, char **copy, int size, t_export export)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < size)
	{
		if (ft_strncmp(env->envp[i], export.key, strlen(export.key)) != 0
			|| env->envp[i][strlen(export.key)] != '=')
		{
			copy[j] = ft_strdup(env->envp[i]);
			j++;
		}
		i++;
	}
	copy[j] = NULL;
}
