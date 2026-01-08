/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:19:19 by jhauvill          #+#    #+#             */
/*   Updated: 2026/01/08 14:38:28 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	put_default_params(t_cmd *cmd)
{
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	cmd->error = false;
	cmd->redir = NULL;
	cmd->next = NULL;
}

static t_cmd	*create_cmd(t_token *tokens)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	if (!tokens || tokens->type == T_PIPE)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	while (tokens && tokens->type != T_PIPE)
	{
		if (tokens->type == T_CMD || tokens->type == T_ARG)
			i++;
		tokens = tokens->next;
	}
	if (i == 0)
		i = 1;
	cmd->args = malloc(sizeof(char *) * (i + 1));
	if (!cmd->args)
		return (free(cmd), NULL);
	cmd->args[0] = NULL;
	put_default_params(cmd);
	return (cmd);
}

static void	add_redir_token(t_cmd *cmd, t_token *token)
{
	t_token	*new_redir;
	t_token	*current;
	char	*str_no_quotes;

	new_redir = malloc(sizeof(t_token));
	if (!new_redir)
		return ;
	if (token->str[0] == '\'' || token->str[0] == '"')
	{
		str_no_quotes = rmv_redir_quotes(token->str);
		new_redir->str = str_no_quotes;
	}
	else
		new_redir->str = token->str;
	new_redir->type = token->type;
	new_redir->next = NULL;
	if (!cmd->redir)
		cmd->redir = new_redir;
	else
	{
		current = cmd->redir;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

static t_cmd	*build_cmd2(t_token *tokens, t_cmd *cmd, int *i)
{
	if (tokens->type == T_PIPE && cmd)
	{
		cmd->args[*i] = NULL;
		if (tokens->next)
			cmd->next = create_cmd(tokens->next);
		if (cmd->next)
		{
			cmd = cmd->next;
			*i = 0;
		}
	}
	if (tokens->type == T_APPEND || tokens->type == T_HEREDOC
		|| tokens->type == T_INPUT || tokens->type == T_TRUNC)
		add_redir_token(cmd, tokens);
	return (cmd);
}

t_cmd	*build_cmd(t_token *tokens, t_data *data)
{
	t_cmd	*head;
	t_cmd	*cmd;
	int		i;
	char	*expanded;

	cmd = create_cmd(tokens);
	head = cmd;
	i = 0;
	while (tokens)
	{
		cmd = build_cmd2(tokens, cmd, &i);
		if (!cmd)
			return (data->last_exit_status = 2, ft_putstr_fd(
					"syntax error near unexpected token `|'\n", 2), NULL);
		if (tokens->type == T_CMD || tokens->type == T_ARG)
		{
			expanded = expand(tokens->str, data);
			if (expanded)
				cmd->args[i++] = expanded;
			else
				cmd->args[i++] = NULL;
		}
		tokens = tokens->next;
	}
	return (cmd->args[i] = NULL, head);
}
