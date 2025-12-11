/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:40:00 by banne             #+#    #+#             */
/*   Updated: 2025/12/11 12:49:51 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->str)
			free(current->str);
		free(current);
		current = next;
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	current = cmds;
	while (current)
	{
		next = current->next;
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				free(current->args[i]);
				i++;
			}
			free(current->args);
		}
		if (current->infile != STDIN_FILENO)
			close(current->infile);
		if (current->outfile != STDOUT_FILENO)
			close(current->outfile);
		free(current);
		current = next;
	}
}

void	cleanup_iteration(t_data *data)
{
	if (!data)
		return ;
	if (data->tokens)
		free_tokens(data->tokens);
	if (data->cmds)
		free_cmds(data->cmds);
	data->tokens = NULL;
	data->cmds = NULL;
}

void	cleanup_all(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->env)
	{
		if (data->env->envp)
		{
			i = 0;
			while (data->env->envp[i])
			{
				free(data->env->envp[i]);
				i++;
			}
			free(data->env->envp);
		}
		if (data->env->pwd)
			free(data->env->pwd);
		if (data->env->oldpwd)
			free(data->env->oldpwd);
		if (data->env->home)
			free(data->env->home);
		free(data->env);
	}
	free(data);
}
