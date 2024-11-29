/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:19:51 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/13 00:09:06 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

void	toggle_mutex(t_mtx *mutex, t_mtx_op operation)
{
	if (operation == LOCK)
		pthread_mutex_lock(mutex);
	else if (operation == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (operation == DESTROY)
		pthread_mutex_destroy(mutex);
	else
		printf("Invalid operation\n");
}

void	destroy_forks(t_simulation *sim, unsigned int num_philos)
{
	unsigned int	i;

	if (sim->forks)
	{
		i = 0;
		while (i < num_philos)
		{
			toggle_mutex(&sim->forks[i].fork, DESTROY);
			i++;
		}
		free(sim->forks);
	}
}

void	destroy_mutexes(t_simulation *sim)
{
	destroy_forks(sim, sim->num_philos);
	toggle_mutex(&sim->print_lock, DESTROY);
	toggle_mutex(&sim->death_lock, DESTROY);
	toggle_mutex(&sim->meal_lock, DESTROY);
}

void	sim_cleanup(t_simulation *sim)
{
	destroy_mutexes(sim);
	if (sim->philos)
		free(sim->philos);
}
