/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:27:55 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/04 17:54:47 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/**
 * Example character 'A'
 * The client sends each bit of the character A (01000001) as a
 * signal to the server.
 * bit_pos: position of the bit in the character being sent.
 * (c >> bit) & 1 checks if the bit at the current pos is 1 (SIGUSR1)
 * or 0 (SIGUSR2).
 *
 * The character is sent from client to the server one bit a time.
 * The client sends SIGUSR1 if the current bit of the character is 1
 * and SIGUSR2 if the current bit is 0.
 *
*/
void	ft_send_message(pid_t server_pid, const char *message)
{
	char	c;
	size_t	i;
	size_t	len;
	int		bit_pos;

	len = ft_strlen(message);
	i = 0;
	while (i <= len)
	{
		c = message[i];
		bit_pos = 0;
		while (bit_pos < BIT_SIZE)
		{
			if ((c >> bit_pos) & 1)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			usleep(100);
			bit_pos++;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	pid_t		server_pid;
	const char	*message;

	if (argc != 3)
	{
		ft_printf("Usage: %s <server_pid> <\"message\">\n", argv[0]);
		return (1);
	}
	server_pid = (pid_t)ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_printf("Error: Invalid Server PID!\n");
		return (1);
	}
	message = argv[2];
	ft_send_message(server_pid, message);
	return (0);
}
