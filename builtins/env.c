/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:36:32 by banne             #+#    #+#             */
/*   Updated: 2025/12/18 18:58:45 by jhauvill         ###   ########.fr       */
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
	int		j;
	int		i;
	char	*underscore;

	i = 0;
	j = 0;
	underscore = NULL;
	while (args[j])
		j++;
	if (j > 1)
	{
		ft_fprintf("env: ", args[1], ": No such file or directory\n");
		return (127);
	}
	while (envp[i])
	{
		if (envp[i][0] == '_' && envp[i][1] == '=')
			underscore = envp[i];
		else if (is_not_empty(envp[i]))
			ft_printf("%s\n", envp[i]);
		i++;
	}
	if (underscore)
		ft_printf("%s\n", underscore);
	return (0);
}
