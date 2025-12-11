/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:36:30 by banne             #+#    #+#             */
/*   Updated: 2025/12/11 11:40:35 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	new_line(int newline)
{
	if (newline)
		printf("\n");
}

static void	print_echo_args(char **args, int start_index)
{
	int	i;

	i = start_index;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

void	ft_echo(char **args)
{
	int	i;
	int	need_newline;
	int	j;

	i = 1;
	need_newline = 1;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
		{
			need_newline = 0;
			i += 1;
		}
		else
			break ;
	}
	print_echo_args(args, i);
	new_line(need_newline);
}
