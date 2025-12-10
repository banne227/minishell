/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:36:40 by banne             #+#    #+#             */
/*   Updated: 2025/12/09 12:48:37 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(void)
{
	char	path_buffer[2048];

	if (getcwd(path_buffer, sizeof(path_buffer)) != NULL)
	{
		printf("%s\n", path_buffer);
	}
	else
	{
		perror("pwd error");
	}
}
