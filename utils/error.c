/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:15:13 by banne             #+#    #+#             */
/*   Updated: 2026/01/08 15:34:10 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_error(int code, t_data *data)
{
	data->last_exit_status = code;
	if (data)
		cleanup_all(data);
	exit(code);
}

void	get_status(int pid, t_data *data)
{
	int	status;
	int	exit_code;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		data->last_exit_status = exit_code;
	}
	else if (WIFSIGNALED(status))
	{
		exit_code = WTERMSIG(status);
		if (exit_code == SIGINT)
			ft_putstr_fd("\n", 2);
		else if (exit_code == SIGQUIT)
			ft_putstr_fd("Quit (core dump): 3\n", 2);
		data->last_exit_status = 128 + exit_code;
	}
}

void	ft_fprintf(char *str1, char *mess, char *str2)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(mess, 2);
	ft_putstr_fd(str2, 2);
}

bool	is_valid(char *cmd)
{
	bool	valid;

	if (!cmd || cmd[0] == '\0')
		return (false);
	if (ft_strcmp(cmd, "..") == 0
		|| ft_strcmp(cmd, ".") == 0 || ft_strcmp(cmd, "~/..") == 0
		|| ft_strcmp(cmd, "~/") == 0 || ft_strcmp(cmd, "../") == 0)
		valid = false;
	else if (ft_strcmp(cmd, "<") == 0 || ft_strcmp(cmd, "<<") == 0
		|| ft_strncmp(cmd, ">", 1) == 0 || ft_strcmp(cmd, ">>") == 0
		|| ft_strncmp(cmd, "|", 1) == 0)
		valid = false;
	else
		valid = true;
	if (!valid)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("'\n", 2);
	}
	return (valid);
}

void	print_cmd_error(t_cmd *cmd, t_data *data)
{
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		data->last_exit_status = 127;
		return ;
	}
	if (ft_strchr(cmd->args[0], '/') && access(cmd->args[0], F_OK) == 0)
	{
		ft_fprintf("minishell: ", cmd->args[0], ":Permission denied\n");
		data->last_exit_status = 126;
	}
	else
	{
		ft_fprintf("minishell: ", cmd->args[0], ":command not found\n");
		data->last_exit_status = 127;
	}
}
