/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 23:37:48 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/13 00:35:05 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	init_forks(t_simulation *sim)
{
	unsigned int	i;

	sim->forks = malloc(sizeof(t_fork) * sim->num_philos);
	if (!sim->forks)
		return (philo_message(PHILO_MALLOC_ERROR, false));
	i = 0;
	while (i < sim->num_philos)
	{
		if (pthread_mutex_init(&sim->forks[i].fork, NULL) != 0)
		{
			destroy_forks(sim, i);
			return (philo_message("Failed to initialize fork mutex", false));
		}
		sim->forks[i].id = i;
		i++;
	}
	return (true);
}

static bool	init_mutexes(t_simulation *sim)
{
	if (pthread_mutex_init(&sim->print_lock, NULL) != 0)
		return (philo_message("Failed to initialize print mutex", false));
	if (pthread_mutex_init(&sim->death_lock, NULL) != 0)
	{
		toggle_mutex(&sim->print_lock, DESTROY);
		return (philo_message("Failed to initialize death mutex", false));
	}
	if (pthread_mutex_init(&sim->meal_lock, NULL) != 0)
	{
		toggle_mutex(&sim->print_lock, DESTROY);
		toggle_mutex(&sim->death_lock, DESTROY);
		return (philo_message("Failed to initialize meal mutex", false));
	}
	if (!init_forks(sim))
	{
		toggle_mutex(&sim->print_lock, DESTROY);
		toggle_mutex(&sim->death_lock, DESTROY);
		toggle_mutex(&sim->meal_lock, DESTROY);
		return (false);
	}
	return (true);
}

static bool	init_philo_fields(t_philosopher *philo, int id,
	t_simulation *sim)
{
	t_time	current_time;

	current_time = get_current_time();
	if (current_time == 0)
		return (false);
	philo->id = id;
	philo->meals_eaten = 0;
	philo->eating = false;
	philo->rip = &sim->rip;
	philo->last_meal_time = current_time;
	philo->sim = sim;
	return (true);
}

static bool	init_philosophers(t_simulation *sim)
{
	unsigned int	i;

	sim->philos = malloc(sizeof(t_philosopher) * sim->num_philos);
	if (!sim->philos)
		return (philo_message(PHILO_MALLOC_ERROR, false));
	i = 0;
	while (i < sim->num_philos)
	{
		if (!init_philo_fields(&sim->philos[i], i, sim))
			return (ft_free_bool(sim->philos, false));
		sim->philos[i].left_fork = &sim->forks[i];
		sim->philos[i].right_fork = &sim->forks[(i + 1) % sim->num_philos];
		if (pthread_create(&sim->philos[i].thread, NULL,
				philosopher_routine, &sim->philos[i]) != 0)
		{
			while (i > 0)
				pthread_detach(sim->philos[--i].thread);
			free(sim->philos);
			return (philo_message(PHILO_ERR_THREAD, false));
		}
		i++;
	}
	return (true);
}

bool	init_simulation(t_simulation *sim)
{
	sim->rip = false;
	sim->stop = false;
	sim->start_time = get_current_time();
	if (sim->start_time == 0)
		return (false);
	if (!init_mutexes(sim) || !init_philosophers(sim))
	{
		sim_cleanup(sim);
		return (false);
	}
	return (true);
}
