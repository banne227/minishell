/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:36:27 by jhauvill          #+#    #+#             */
/*   Updated: 2025/12/11 16:03:39 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	init_all(t_data *data, char **envp)
{
	data->env = malloc(sizeof(t_env));
	if (!data->env)
	{
		free(data);
		return (1);
	}
	data->env->envp = env_init(envp);
	data->env->pwd = NULL;
	data->env->oldpwd = NULL;
	data->env->home = NULL;
	if (!data->env->envp)
	{
		free(data->env);
		free(data);
		return (1);
	}
	set_envp_paths(data->env);
	data->tokens = NULL;
	data->cmds = NULL;
	data->cmd_count = 0;
	data->here_doc = 0;
	data->eof_str = NULL;
	data->last_exit_status = 0;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	*data;

	(void) argc;
	(void) argv;
	data = malloc(sizeof(t_data));
	if (!data || init_all(data, envp) == 1)
		return (1);
	while (1)
	{
		setup_prompt_signals();
		line = readline(BLUE "minishell$" RESET " ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		data->tokens = lexer(line);
		data->cmds = build_cmd(data->tokens);
		data->cmd_count = count_cmd_data(data);
		exec_cmd(data);
		cleanup_iteration(data);
		free(line);
	}
	cleanup_all(data);
	return (0);
}
