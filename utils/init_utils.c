/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:00:39 by banne             #+#    #+#             */
/*   Updated: 2025/12/09 16:28:34 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_cmd_data(t_data *data)
{
	int		count;
	t_cmd	*tmp;

	count = 0;
	tmp = data->cmds;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}
