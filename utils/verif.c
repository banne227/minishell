/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:05:26 by banne             #+#    #+#             */
/*   Updated: 2026/01/08 17:07:12 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	verif_home_dir(t_env *env)
{
	char	*home;
	bool	result;

	home = get_env(env, "HOME");
	if (!home || access(home, F_OK) != 0)
	{
		ft_putstr_fd("cd: Home  not set\n", 2);
		free(home);
		return (false);
	}
	result = true;
	free(home);
	return (result);
}

bool	verif_oldpwd_dir(const char *oldpath)
{
	if (!oldpath || access(oldpath, F_OK) != 0)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (false);
	}
	return (true);
}

bool	verif_curr_dir(const char *curr)
{
	if (!curr || access(curr, F_OK) != 0)
		return (false);
	return (true);
}

int	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

void	put_void(void)
{
	return ;
}
