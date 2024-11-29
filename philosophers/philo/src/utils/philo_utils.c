/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:16:32 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/13 03:44:36 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

void	ft_putstr_fd(char *str, int fd)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	if (str)
		write(fd, str, len);
}

/* Get the current time in milliseconds */
t_time	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		ft_putstr_fd("Error: gettimeofday() failed\n", STDERR_FILENO);
		return ((t_time)0);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

bool	philo_message(char *str, bool value)
{
	if (str)
		printf("%s\n", str);
	return (value);
}

bool	ft_free_bool(void *ptr, bool return_value)
{
	if (ptr)
		free(ptr);
	return (return_value);
}

void	ft_usleep(t_time time_in_ms)
{
	t_time	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < time_in_ms)
		usleep(500);
}
