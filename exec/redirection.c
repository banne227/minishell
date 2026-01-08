/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:34:05 by banne             #+#    #+#             */
/*   Updated: 2025/12/15 12:38:18 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_input_file(t_cmd *cmd, const char *file)
{
	if (cmd->infile != STDIN_FILENO)
		close(cmd->infile);
	cmd->infile = open(file, O_RDONLY);
	if (cmd->infile < 0)
		return (put_error(cmd, "failed to open input file"));
	return (cmd->infile);
}

int	open_output_trunc(t_cmd *cmd, const char *file)
{
	if (cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
	cmd->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->outfile < 0)
		return (put_error(cmd, "failed to open output file"));
	return (cmd->outfile);
}

int	open_output_append(t_cmd *cmd, const char *file)
{
	if (cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
	cmd->outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->outfile < 0)
		return (put_error(cmd, "failed to open output file"));
	return (cmd->outfile);
}

void	do_redirections(t_cmd *cmd)
{
	if (cmd->infile != STDIN_FILENO)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
		{
			put_error(cmd, "dup2 infile failed");
			return ;
		}
		close(cmd->infile);
		cmd->infile = STDIN_FILENO;
	}
	if (cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
		{
			put_error(cmd, "dup2 outfile failed");
			return ;
		}
		close(cmd->outfile);
		cmd->outfile = STDOUT_FILENO;
	}
}

void	apply_redirections_to_cmd(t_cmd *cmd, t_data *data)
{
	t_token	*current;

	if (!cmd || !cmd->redir)
		return ;
	current = cmd->redir;
	while (current)
	{
		if (current->type == T_INPUT)
			cmd->infile = open_input_file(cmd, current->str);
		else if (current->type == T_HEREDOC)
			cmd->infile = create_heredoc(cmd, current->str, data);
		else if (current->type == T_TRUNC)
			cmd->outfile = open_output_trunc(cmd, current->str);
		else if (current->type == T_APPEND)
			cmd->outfile = open_output_append(cmd, current->str);
		current = current->next;
	}
}
