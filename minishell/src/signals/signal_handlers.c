/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bproton <bproton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:54:09 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/02 15:03:00 by bproton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

void	handle_sigint_heredoc(int signum)
{
	(void)signum;
	g_signal_status = 1;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// /* Signal handler for Ctrl-C (SIGINT) */
void	handle_sigint(int signum)
{
	g_signal_status = signum;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	child_handle_sigint(int signum)
{
	if (signum == SIGINT)
		g_signal_status = 130;
	else
	{
		ft_putstr_fd("Quit", 1);
		g_signal_status = 131;
	}
}

void	setup_signals(void)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_handler = &handle_sigint;
	sigemptyset(&sa_sigint.sa_mask);
	sa_sigint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_sigint, NULL);
	sa_sigquit.sa_handler = SIG_IGN;
	sigemptyset(&sa_sigquit.sa_mask);
	sa_sigquit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

void	setup_child_signals(void)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_handler = &child_handle_sigint;
	sigemptyset(&sa_sigint.sa_mask);
	sa_sigint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_sigint, NULL);
	sa_sigquit.sa_handler = SIG_IGN;
	sigemptyset(&sa_sigquit.sa_mask);
	sa_sigquit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}
