/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bproton <bproton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:18:00 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/02 14:42:48 by bproton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNALS_H
# define MS_SIGNALS_H

# include <signal.h>
# include <termios.h>

/* Store the signal number */
extern volatile sig_atomic_t	g_signal_status;

void	handle_ctrl_d(char *input);
void	setup_signals(void);
void	setup_child_signals(void);
void	handle_sigint_heredoc(int signum);
void	ft_heredoc_test(void);

#endif
