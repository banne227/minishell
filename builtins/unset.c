/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:36:42 by banne             #+#    #+#             */
/*   Updated: 2025/12/09 12:48:30 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_valid_identifier(char *arg)
{
	int	i;

	i = 1;
	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (false);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	env_exist(t_env *env, char *arg)
{
	int	i;
	int	len;

	i = 0;
	len = strlen(arg);
	while (env->envp[i])
	{
		if (ft_strncmp(env->envp[i], arg, len) == 0 && env->envp[i][len] == '=')
			return (true);
		i++;
	}
	return (false);
}

void	ft_unset(char **args, t_env *env)
{
	int			i;
	t_export	to_remove;
	char		**new_envp;

	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]) && env_exist(env, args[i]))
		{
			to_remove.key = args[i];
			to_remove.value = NULL;
			to_remove.type = EXPORT_INVALID;
			new_envp = env_remove(env, to_remove);
			if (new_envp)
			{
				free_envp(env->envp);
				env->envp = new_envp;
			}
		}
		i++;
	}
}
