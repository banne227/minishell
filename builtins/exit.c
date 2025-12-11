/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:36:35 by banne             #+#    #+#             */
/*   Updated: 2025/12/11 11:35:11 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	numeric_argument_required(char *arg)
{
	fprintf(stderr, "exit: %s: numeric argument required\n", arg);
	return (255);
}

int	ft_exit(char **args, t_data *data)
{
	int	status;
	int	i;

	i = 0;
	status = data->last_exit_status;
	printf("exit\n");
	if (args[1][i] == '+' || args[1][i] == '-')
		i++;
	while (args[1] && args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
			exit(numeric_argument_required(args[1]));
		i++;
	}
	if (args[1] && args[2])
	{
		fprintf(stderr, "exit: too many arguments\n");
		return (1);
	}
	if (args[1])
		status = (atoll(args[1]) % 256 + 256) % 256;
	//free toute la mémoire
	exit(status);
}
