/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:36:32 by banne             #+#    #+#             */
/*   Updated: 2025/12/09 12:45:46 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	is_not_empty(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

int	ft_env(char **args, char **envp)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (args[j])
		j++;
	if (j > 1)
	{
		fprintf(stderr, "env: %s : No such file or directory\n", args[1]);
		return (127);
	}
	while (envp[i])
	{
		if (is_not_empty(envp[i]))
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
