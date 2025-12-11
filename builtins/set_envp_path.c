/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 18:12:34 by banne             #+#    #+#             */
/*   Updated: 2025/12/11 11:39:35 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_home_directory(t_env *env)
{
	int	i;

	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp(env->envp[i], "HOME=", 5) == 0)
			return (env->envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_oldpwd_directory(t_env *env)
{
	int	i;

	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp(env->envp[i], "OLDPWD=", 7) == 0)
			return (env->envp[i] + 7);
		i++;
	}
	return (NULL);
}

char	*get_current_directory(void)
{
	char	*pwd;
	char	*dup;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		dup = ft_strdup(pwd);
		free(pwd);
		return (dup);
	}
	return (NULL);
}

bool	verif_dir(const char *home, const char *oldpath, const char *current)
{
	if (access(home, F_OK) != 0)
	{
		fprintf(stderr, "cd: Home  not set\n");
		return (false);
	}
	if (access(oldpath, F_OK) != 0)
	{
		fprintf(stderr, "cd: OLDPWD not set\n");
		return (false);
	}
	if (access(current, F_OK) != 0)
	{
		fprintf(stderr, "cd: PWD not set\n");
		return (false);
	}
	return (true);
}

void	set_envp_paths(t_env *env)
{
	char	*temp_home;
	char	*temp_oldpwd;
	char	*temp_pwd;

	if (!env || !env->envp)
		return ;
	temp_home = get_home_directory(env);
	temp_oldpwd = get_oldpwd_directory(env);
	temp_pwd = get_current_directory();
	if (env->home)
		free(env->home);
	if (env->oldpwd)
		free(env->oldpwd);
	if (env->pwd)
		free(env->pwd);
	if (temp_home)
		env->home = ft_strdup(temp_home);
	else
		env->home = NULL;
	if (temp_oldpwd)
		env->oldpwd = ft_strdup(temp_oldpwd);
	else
		env->oldpwd = NULL;
	env->pwd = temp_pwd;
}
