/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:36:27 by banne             #+#    #+#             */
/*   Updated: 2025/12/10 10:32:34 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_env_paths(t_env *env)
{
	char	**envp;
	char	**old_envp;
	int		i;

	envp = new_envp(env);
	if (!envp)
		return ;
	old_envp = env->envp;
	env->envp = envp;
	set_envp_paths(env);
	if (old_envp)
	{
		i = 0;
		while (old_envp[i])
		{
			free(old_envp[i]);
			i++;
		}
		free(old_envp);
	}
}

int	no_file_or_dir(char *path)
{
	fprintf(stderr, "cd: %s: No such file or directory\n", path);
	return (1);
}

int	ft_cd(char **args, t_env *env)
{
	if (!verif_dir(env->home, env->oldpwd, env->pwd))
		return (1);
	if (!args[1])
	{
		if (chdir(env->home) == -1)
			return (no_file_or_dir(env->home));
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (chdir(env->oldpwd) == -1)
			return (no_file_or_dir(env->oldpwd));
		printf("%s\n", env->oldpwd);
	}
	else
	{
		if (chdir(args[1]) == -1)
			return (no_file_or_dir(args[1]));
	}
	update_env_paths(env);
	return (0);
}
