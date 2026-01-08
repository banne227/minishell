/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:49:26 by jhauvill          #+#    #+#             */
/*   Updated: 2025/12/23 10:13:48 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tabl(char **tabl)
{
	int	i;

	if (!tabl)
		return ;
	i = 0;
	while (tabl[i])
	{
		free(tabl[i]);
		i++;
	}
	free(tabl);
}

void	free_data(t_data *data)
{
	if (data->env->pwd)
		free(data->env->pwd);
	if (data->env->oldpwd)
		free(data->env->oldpwd);
	if (data->env->home)
		free(data->env->home);
	free(data->env);
}

void	free_all_pipelines(t_pipe pipex, int nbr)
{
	if (!pipex.orig_data)
		return ;
	if (pipex.orig_data->tokens)
		free_tokens(pipex.orig_data->tokens);
	if (pipex.orig_data->cmds)
		free_cmds(pipex.orig_data->cmds);
	if (pipex.orig_data->env)
	{
		if (pipex.orig_data->env->envp)
			free_tabl(pipex.orig_data->env->envp);
		free_data(pipex.orig_data);
	}
	if (pipex.pipe_fd)
		free_all_pipes(pipex.pipe_fd, nbr);
	if (pipex.pids)
		free(pipex.pids);
	if (pipex.orig_data->need_free)
		free(pipex.orig_data);
}
