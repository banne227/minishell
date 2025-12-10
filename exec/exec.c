/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:33:53 by banne             #+#    #+#             */
/*   Updated: 2025/12/09 17:39:36 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_builtin_in_parent(t_cmd *cmd)
{
	if (cmd == NULL)
		return (false);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (true);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (true);
	return (false);
}

void	run_builtin_in_parent(t_cmd *cmd, t_env *env, t_data *data)
{
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit(cmd->args, data);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		ft_cd(cmd->args, env);
	//else if (ft_strcmp(cmd->args[0], "export") == 0)
	//	ft_export(cmd->args, env);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ft_unset(cmd->args, env);
}

void	exec_cmd(t_data *data)
{
	int		i;
	pid_t	pid;	

	i = 0;
	if (!data->cmds || !data->cmds->args[0])
		return ;
	if (count_pipes(data->tokens) > 0)
		return (exec_pipeline(data->cmds, data->env, data->tokens));
	if (is_builtin_in_parent(data->cmds))
	{
		run_builtin_in_parent(data->cmds, data->env, data);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
		exec_child(data->cmds, data->env, data->tokens);
	else
		waitpid(pid, NULL, 0);
}

