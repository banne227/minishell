/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:55:16 by jhauvill          #+#    #+#             */
/*   Updated: 2025/12/09 15:49:40 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//void	setup_signal(void)
//{
//	signal(SIGINT, stop_signal);
//	signal(SIGQUIT, stop_signal);
//}

//int	stop_signal(int sig)
//{
//	return (1);
//}

static void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
