/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:36:27 by jhauvill          #+#    #+#             */
/*   Updated: 2025/12/22 12:02:33 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

extern int	g_exit_status;

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
	data->last_exit_status = 0;
	data->need_free = true;
	return (0);
}

static void	void_args(int argc, char **argv)
{
	(void) argc;
	(void) argv;
}

char	*readline_prompt(void)
{
	char	*line;

	setup_prompt_signals();
	line = readline(BLUE "minishell$" RESET " ");
	if (!line)
	{
		ft_printf("exit\n");
		return (NULL);
	}
	if (*line)
		add_history(line);
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	*data;

	void_args(argc, argv);
	data = malloc(sizeof(t_data));
	if (!data || init_all(data, envp) == 1)
		return (1);
	while (1)
	{
		line = readline_prompt();
		if (!line)
			break ;
		if (g_exit_status != 0)
			put_signal(data);
		data->tokens = lexer(line);
		if (data->tokens)
		{
			data->cmds = build_cmd(data->tokens, data);
			data->cmd_count = count_cmd_data(data);
			exec_cmd(data);
		}
		cleanup_iteration_n_line(data, line);
	}
	return (cleanup_all(data), 0);
}
