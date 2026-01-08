/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:36:27 by banne             #+#    #+#             */
/*   Updated: 2026/01/08 10:53:39 by banne            ###   ########.fr       */
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
	ft_fprintf("cd: ", path, ": No such file or directory\n");
	return (1);
}

char	*get_previous_dir(char *current_pwd)
{
	char	*last_slash;
	char	*previous_pwd;
	size_t	len;

	last_slash = ft_strrchr(current_pwd, '/');
	if (!last_slash || last_slash == current_pwd)
		return ("/");
	len = last_slash - current_pwd;
	previous_pwd = malloc(len + 1);
	if (!previous_pwd)
		return (NULL);
	ft_memcpy(previous_pwd, current_pwd, len);
	previous_pwd[len] = '\0';
	return (previous_pwd);
}

int	cd_path(char *path)
{
	if (chdir(path) == -1)
		return (1);
	return (0);
}

int	ft_cd(char **args, t_env *env)
{
	char	*prev;
	char	*target;

	target = args[1];
	if (!target || ft_strcmp(target, "~") == 0)
	{
		if (!verif_home_dir(env))
			return (1);
		target = env->home;
	}
	if (ft_strcmp(target, "-") == 0)
	{
		if (!verif_oldpwd_dir(env->oldpwd))
			return (1);
		target = env->oldpwd;
		ft_printf("%s\n", target);
	}
	if (!target || chdir(target) == -1)
		return (no_file_or_dir(target));
	else if (ft_strcmp(target, "..") == 0)
	{
		prev = get_previous_dir(env->pwd);
		free(prev);
	}
	return (update_env_paths(env), 0);
}
