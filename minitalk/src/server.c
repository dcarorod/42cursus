/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:17:08 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/04 18:07:11 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	print_pid(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("Server started! PID: %d\n", pid);
}

/**
 * SIGUSR1: this bit is 1
 * SIGUSR2: this bit is 0
 * bit_pos: position of the bit  in the character
 * being processed.
 * If bit_pos = 8, all the bits for one character
 * have been received
 *
 *  c |= (1 << bit_pos); // Set the bit at position bit_pos
 * c &= ~(1 << bit_pos); // Clear the bit at position bit_pos
*/
void	ft_signal_handler(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	bit_pos = 0;

	(void)info;
	(void)context;
	if (sig == SIGUSR1)
		c |= (1 << bit_pos);
	else if (sig == SIGUSR2)
		c &= ~(1 << bit_pos);
	bit_pos++;
	if (bit_pos == BIT_SIZE)
	{
		if (c == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", c);
		bit_pos = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	print_pid();
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
