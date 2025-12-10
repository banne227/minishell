/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:36:27 by jhauvill          #+#    #+#             */
/*   Updated: 2025/12/10 11:07:44 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_cmd_debug(t_cmd *cmds)
{
    t_cmd	*current;
    int		cmd_idx;
    int		arg_idx;

    current = cmds;
    cmd_idx = 0;
    while (current)
    {
        printf("[CMD %d]\n", cmd_idx);
        arg_idx = 0;
        while (current->args[arg_idx])
        {
            printf("  args[%d]: %s\n", arg_idx, current->args[arg_idx]);
            arg_idx++;
        }
        printf("  infile: %d | outfile: %d\n", current->infile, current->outfile);
        current = current->next;
        cmd_idx++;
    }
}


int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	*data;

	(void) argc;
	(void) argv;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->env = malloc(sizeof(t_env));
	if (!data->env)
	{
		free(data);
		return (1);
	}
	data->env->envp = env_init(envp);
	if (!data->env->envp)
	{
		free(data->env);
		free(data);
		return (1);
	}
	set_envp_paths(data->env);
	while (1)
	{
		setup_prompt_signals();
		line = readline(BLUE "minishell$" RESET " ");
		if (!line)
			break;
		if (*line)
			add_history(line);
		data->tokens = lexer(line);
		data->cmds = build_cmd(data->tokens);
		print_cmd_debug(data->cmds); // for testing --- IGNORE ---
		data->cmd_count = count_cmd_data(data);
		exec_cmd(data);
		cleanup_iteration(data);
		free(line);
		setup_prompt_signals();
	}
	return (0);
}
