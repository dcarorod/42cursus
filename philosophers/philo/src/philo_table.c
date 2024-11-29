/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:01:02 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/14 17:37:06 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	eat(t_philosopher *philo)
{
	toggle_mutex(&philo->sim->meal_lock, LOCK);
	print_status(philo, EATING);
	philo->eating = true;
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	toggle_mutex(&philo->sim->meal_lock, UNLOCK);
	ft_usleep(philo->sim->time_to_eat);
	philo->eating = false;
}

void	grab_forks_and_eat(t_philosopher *philo)
{
	t_fork			*left;
	t_fork			*right;

	if (philo->id % 2 == 0)
	{
		left = philo->left_fork;
		right = philo->right_fork;
	}
	else
	{
		left = philo->right_fork;
		right = philo->left_fork;
	}
	toggle_mutex(&left->fork, LOCK);
	print_status(philo, TOOK_FORK);
	toggle_mutex(&right->fork, LOCK);
	print_status(philo, TOOK_FORK);
	eat(philo);
	toggle_mutex(&left->fork, UNLOCK);
	toggle_mutex(&right->fork, UNLOCK);
}

static void	take_siesta(t_philosopher *philo)
{
	t_time	current_time;
	t_time	elapsed_time;
	t_time	remaining_ttd;

	print_status(philo, SLEEPING);
	current_time = get_current_time();
	elapsed_time = current_time - philo->last_meal_time;
	remaining_ttd = philo->sim->time_to_die - elapsed_time;
	if (remaining_ttd < philo->sim->time_to_sleep)
		ft_usleep(remaining_ttd);
	else
		ft_usleep(philo->sim->time_to_sleep);
}

void	*handle_lonely_philo(t_philosopher *philo)
{
	toggle_mutex(&philo->left_fork->fork, LOCK);
	print_status(philo, TOOK_FORK);
	toggle_mutex(&philo->left_fork->fork, UNLOCK);
	ft_usleep(philo->sim->time_to_die);
	print_status(philo, RIP);
	return (NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	int				max_meals;

	philo = (t_philosopher *)arg;
	if (philo->sim->num_philos == 1)
		return (handle_lonely_philo(philo));
	max_meals = philo->sim->meals_required;
	while (!philo->sim->stop)
	{
		if (philo_starved(philo))
			break ;
		if (*(philo->rip))
			break ;
		grab_forks_and_eat(philo);
		if (max_meals != -1 && philo->meals_eaten == max_meals)
			break ;
		take_siesta(philo);
		if (philo_starved(philo))
			break ;
		print_status(philo, THINKING);
	}
	return (NULL);
}
