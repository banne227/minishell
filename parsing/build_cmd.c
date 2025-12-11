/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:19:19 by jhauvill          #+#    #+#             */
/*   Updated: 2025/12/11 15:20:37 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//void	print_tokens(t_token *tokens)
//{
//    const char *types[] = {"", "T_INPUT", "T_HEREDOC", "T_TRUNC", "T_APPEND", "T_PIPE", "T_CMD", "T_ARG"};
//    while (tokens)
//    {
//        printf(RED"Token: '%s', Type: %s (%d)\n"RESET, tokens->str, types[tokens->type], tokens->type);
//        tokens = tokens->next;
//    }
//}

static t_cmd	*create_cmd(t_token *tokens)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	while (tokens)
	{
		if (tokens->type == T_CMD || tokens->type == T_ARG)
			i++;
		if (tokens->type == T_PIPE)
			break ;
		tokens = tokens->next;
	}
	if (i == 0)
		i = 1;
	cmd->args = malloc(sizeof(char *) * (i + 1));
	if (!cmd->args)
		return (NULL);
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	cmd->next = NULL;
	cmd->error = false;
	return (cmd);
}



t_cmd	*build_cmd(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*cmd;
	int		i;
	int		redir_i;
	char	*expanded;

	cmd = create_cmd(tokens);
	head = cmd;
	i = 0;
	redir_i = 0;
	//print_tokens(tokens);
	while (tokens)
	{
		if (tokens->type == T_PIPE)
		{
			cmd->args[i] = NULL;
			cmd->next = create_cmd(tokens);
			cmd = cmd->next;
			i = 0;
		}
		if (tokens->type == T_APPEND || tokens->type == T_HEREDOC
			|| tokens->type == T_INPUT || tokens->type == T_TRUNC)
		{
			cmd->redir[redir_i] = (*tokens);
			i++;
		}
		else if (tokens->type == T_CMD || tokens->type == T_ARG)
		{
			expanded = expand(tokens->str);
			if (expanded)
				cmd->args[i] = expanded;
			else
				cmd->args[i] = NULL;
			i++;
		}
		tokens = tokens->next;
	}
	cmd->args[i] = NULL;
	return (head);
}
