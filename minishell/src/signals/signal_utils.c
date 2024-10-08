/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:41:49 by bproton           #+#    #+#             */
/*   Updated: 2024/10/02 15:31:52 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_heredoc_test(void)
{
	struct sigaction	act;

	act.sa_handler = &handle_sigint_heredoc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
}

/*	Function to handle Ctrl-D (EOF)
	When Ctrl-D is pressed, input is NULL */
void	handle_ctrl_d(char *input)
{
	if (!input)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(0);
	}
}
