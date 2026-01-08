/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:35:30 by jhauvill          #+#    #+#             */
/*   Updated: 2026/01/08 13:44:51 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

void	handle_sigint_prompt(int sig)
{
	(void)sig;
	g_exit_status = 130;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit_prompt(int sig)
{
	(void)sig;
	g_exit_status = 131;
}

void	setup_prompt_signals(void)
{
	signal(SIGINT, handle_sigint_prompt);
	signal(SIGQUIT, handle_sigquit_prompt);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	put_signal(t_data *data)
{
	data->last_exit_status = g_exit_status;
	g_exit_status = 0;
}
