/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 09:15:46 by banne             #+#    #+#             */
/*   Updated: 2025/12/11 13:55:30 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	sort_env(char **envp)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
			j++;
		}
		i++;
	}
}

int	print_export(t_env *env)
{
	int		i;
	char	**envp_sorted;

	i = 0;
	envp_sorted = malloc(sizeof(char *) * (get_env_size(env) + 1));
	if (!envp_sorted)
		return (1);
	envp_sorted[get_env_size(env)] = NULL;
	copy_env(env, envp_sorted);
	if (!envp_sorted)
		return (1);
	sort_env(envp_sorted);
	while (envp_sorted[i])
	{
		printf("declare -x %s\n", envp_sorted[i]);
		i++;
	}
	return (0);
}
