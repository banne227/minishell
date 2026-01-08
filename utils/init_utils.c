/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:00:39 by banne             #+#    #+#             */
/*   Updated: 2025/12/19 11:00:13 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_cmd_data(t_data *data)
{
	int		count;
	t_cmd	*tmp;

	count = 0;
	if (!data || !data->cmds)
		return (0);
	tmp = data->cmds;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int	count_pipes(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == T_PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

int	put_error(t_cmd *cmd, const char *msg)
{
	cmd->error = true;
	ft_fprintf("minishell: ", (char *)msg, "\n");
	return (-1);
}
