/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:36:27 by banne             #+#    #+#             */
/*   Updated: 2025/12/11 15:56:54 by banne            ###   ########.fr       */
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

	if (!verif_dir(env->home, env->oldpwd, env->pwd))
		return (1);
	target = args[1];
	if (!target)
		target = env->home;
	if (ft_strcmp(target, "-") == 0)
	{
		target = env->oldpwd;
		printf("%s\n", target);
	}
	if (!target || chdir(target) == -1)
		return (no_file_or_dir(target));
	else if (ft_strcmp(target, "..") == 0)
	{
		prev = get_previous_dir(env->pwd);
		free(prev);
	}
	update_env_paths(env);
	return (0);
}
