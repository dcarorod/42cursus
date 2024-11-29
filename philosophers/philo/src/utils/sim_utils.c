/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:47:01 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/14 17:33:17 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

void	print_status(t_philosopher *philo, t_state state)
{
	char			*status;

	if (state == EATING)
		status = PHILO_EATS;
	else if (state == SLEEPING)
		status = PHILO_SLEEPS;
	else if (state == THINKING)
		status = PHILO_THINKS;
	else if (state == TOOK_FORK)
		status = PHILO_FORK;
	else if (state == RIP)
		status = PHILO_RIP;
	else
		return ;
	toggle_mutex(&philo->sim->print_lock, LOCK);
	if (!philo->sim->stop)
		printf("%lu %d %s\n", get_current_time(), philo->id + 1, status);
	toggle_mutex(&philo->sim->print_lock, UNLOCK);
}

bool	rip_philo(t_simulation *sim, t_philosopher *philo)
{
	toggle_mutex(&sim->death_lock, LOCK);
	*(philo->rip) = true;
	print_status(philo, RIP);
	sim->stop = true;
	toggle_mutex(&sim->death_lock, UNLOCK);
	return (true);
}

bool	wait_death(t_philosopher *philo)
{
	t_simulation	*sim;
	long			time_to_think;

	sim = philo->sim;
	time_to_think = sim->time_to_die - (sim->time_to_eat + sim->time_to_sleep);
	if (time_to_think <= 0)
		return (rip_philo(sim, philo));
	else
	{
		ft_usleep(time_to_think);
		return (rip_philo(sim, philo));
	}
}

bool	philo_starved(t_philosopher *philo)
{
	t_simulation	*sim;
	t_time			current_time;
	t_time			time_since_last_meal;

	sim = philo->sim;
	current_time = get_current_time();
	time_since_last_meal = current_time - philo->last_meal_time;
	if (sim->num_philos % 2 == 0
		&& !philo->eating
		&& (philo->meals_eaten > 0
			&& sim->time_to_eat > (sim->time_to_die / 2)))
	{
		return (wait_death(philo));
	}
	if (sim->num_philos % 2 == 1
		&& !philo->eating
		&& (philo->meals_eaten > 0
			&& sim->time_to_eat > (sim->time_to_die / 3)))
		return (wait_death(philo));
	else if (time_since_last_meal > sim->time_to_die)
		return (rip_philo(sim, philo));
	return (false);
}
