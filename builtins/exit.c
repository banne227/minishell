/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:36:35 by banne             #+#    #+#             */
/*   Updated: 2025/12/22 16:53:02 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	numeric_argument_required(char *arg)
{
	ft_fprintf("exit: ", arg, ": numeric argument required\n");
	return (255);
}

static void	cleanningup_and_exit(t_data *data, int status)
{
	cleanup_iteration_n_line(data, NULL);
	cleanup_all(data);
	exit(status);
}

static int	return_to_many_arguments(t_data *data)
{
	(void) data;
	ft_putstr_fd("exit: too many arguments\n", 2);
	return (1);
}

int	ft_exit(char **args, t_data *data)
{
	int	status;
	int	i;

	i = 0;
	status = data->last_exit_status;
	ft_printf("exit\n");
	if (args[1])
	{
		if (args[1][i] == '+' || args[1][i] == '-')
			i++;
		while (args[1] && args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
				cleanningup_and_exit(data, numeric_argument_required(args[1]));
			i++;
		}
		if (args[1] && args[2])
			return (return_to_many_arguments(data));
		if (args[1])
			status = (atoll(args[1]) % 256 + 256) % 256;
	}
	cleanup_iteration_n_line(data, NULL);
	cleanup_all(data);
	exit(status);
	return (0);
}
