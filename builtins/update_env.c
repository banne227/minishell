/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 18:46:13 by banne             #+#    #+#             */
/*   Updated: 2025/12/17 11:08:53 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	have_to_update(const char *env_str)
{
	if (ft_strncmp(env_str, "PWD=", 4) == 0)
		return (true);
	if (ft_strncmp(env_str, "OLDPWD=", 7) == 0)
		return (true);
	return (false);
}

static char	*update_dir(const char *env_str, t_env *env)
{
	char	*tmp;
	char	*res;

	if (ft_strncmp(env_str, "PWD=", 4) == 0)
	{
		tmp = get_current_directory();
		if (!tmp)
			return (NULL);
		res = ft_strjoin("PWD=", tmp);
		free(tmp);
		return (res);
	}
	if (ft_strncmp(env_str, "OLDPWD=", 7) == 0)
		return (ft_strjoin("OLDPWD=", env->pwd));
	return (NULL);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i])
			free(envp[i]);
		i++;
	}
	if (envp)
		free(envp);
}

char	**new_envp(t_env *env)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (env->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (env->envp[i])
	{
		if (have_to_update(env->envp[i]))
			new_envp[i] = update_dir(env->envp[i], env);
		else
			new_envp[i] = ft_strdup(env->envp[i]);
		if (!new_envp[i])
			return (NULL);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
