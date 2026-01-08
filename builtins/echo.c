/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:36:30 by banne             #+#    #+#             */
/*   Updated: 2026/01/08 15:02:07 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	new_line(int newline)
{
	if (newline)
		ft_printf("\n");
}

static void	ft_print(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\\')
			ft_printf("%c", str[i]);
		i++;
	}
}

static void	print_echo_args(char **args, int start_index)
{
	int	i;

	i = start_index;
	if (!args[i])
		return ;
	while (args[i] && args[i + 1])
	{
		ft_print(args[i]);
		if (args[i][0] && args[i + 1][0])
			ft_printf(" ");
		i++;
	}
	if (args[i])
		ft_print(args[i]);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	need_newline;
	int	j;

	i = 1;
	need_newline = 1;
	if (!cmd || !cmd->args || cmd->outfile == -1)
		return ;
	while (cmd->args[i] && cmd->args[i][0] == '-' && cmd->args[i][1] == 'n')
	{
		j = 2;
		while (cmd->args[i][j] == 'n')
			j++;
		if (cmd->args[i][j] == '\0')
		{
			need_newline = 0;
			i += 1;
		}
		else
			break ;
	}
	print_echo_args(cmd->args, i);
	new_line(need_newline);
}
