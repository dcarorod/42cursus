/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:37:24 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/14 17:02:03 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

static bool	parse_arguments(char **argv, t_simulation *sim)
{
	int	meals;

	sim->num_philos = ft_atol(argv[1]);
	sim->time_to_die = ft_atol(argv[2]);
	sim->time_to_eat = ft_atol(argv[3]);
	sim->time_to_sleep = ft_atol(argv[4]);
	if (sim->time_to_die < 1 || sim->time_to_die > FT_INT_MAX
		|| sim->time_to_eat < 1 || sim->time_to_eat > FT_INT_MAX
		|| sim->time_to_sleep < 1 || sim->time_to_sleep > FT_INT_MAX)
		return (philo_message("Invalid time argument", false));
	if (sim->num_philos < 1 || sim->num_philos > PHILO_MAX)
		return (philo_message(PHILO_ERR_NUMBER, false));
	if (argv[5])
	{
		meals = ft_atol(argv[5]);
		if (meals < 1 || meals > FT_INT_MAX)
			return (philo_message(PHILO_MEALS_ERROR, false));
		sim->meals_required = meals;
	}
	else
		sim->meals_required = -1;
	sim->stop = false;
	return (true);
}

static void	join_philo_threads(t_simulation *sim)
{
	unsigned int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (argc != 5 && argc != 6)
	{
		printf("%s\n", PHILO_USAGE);
		return (EXIT_FAILURE);
	}
	if (!parse_arguments(argv, &sim) || !init_simulation(&sim))
		return (EXIT_FAILURE);
	join_philo_threads(&sim);
	sim_cleanup(&sim);
	return (EXIT_SUCCESS);
}
