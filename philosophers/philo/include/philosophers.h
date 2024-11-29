/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:55:21 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/14 17:01:56 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

# define PHILO_THINKS "is thinking"
# define PHILO_EATS "is eating"
# define PHILO_FORK "has taken a fork"
# define PHILO_SLEEPS "is sleeping"
# define PHILO_RIP "died"
# define PHILO_MEALS_ERROR "Number of meals must a positive integer"
# define PHILO_MALLOC_ERROR "Error: Memory allocation failed"
# define PHILO_USAGE "Usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]"
# define PHILO_ERR_NUMBER "The number of philosophers must be bettween 1-200"
# define PHILO_ERR_THREAD "Failed to create philosopher thread"

# define PHILO_MAX 200
# define FT_INT_MAX 2147483647

typedef unsigned long	t_time;
typedef pthread_mutex_t	t_mtx;
struct					s_simulation;

typedef enum e_state
{
	TOOK_FORK,
	EATING,
	THINKING,
	SLEEPING,
	RIP
}	t_state;

typedef enum e_mtx_op
{
	LOCK,
	UNLOCK,
	DESTROY
}	t_mtx_op;

typedef struct s_fork
{
	t_mtx			fork;
	unsigned int	id;
}	t_fork;

typedef struct s_philosopher
{
	unsigned int		id;
	bool				eating;
	bool				*rip;
	int					meals_eaten;
	t_time				last_meal_time;
	pthread_t			thread;
	t_fork				*left_fork;
	t_fork				*right_fork;
	struct s_simulation	*sim;
}	t_philosopher;

typedef struct s_simulation
{
	unsigned int	num_philos;
	t_time			time_to_die;
	t_time			time_to_eat;
	t_time			time_to_sleep;
	int				meals_required;
	bool			rip;
	bool			stop;
	t_philosopher	*philos;
	t_fork			*forks;
	t_mtx			print_lock;
	t_mtx			death_lock;
	t_mtx			meal_lock;
	t_time			start_time;
}	t_simulation;

/* Utils */
void	ft_putstr_fd(char *str, int fd);
bool	philo_message(char *str, bool value);
t_time	get_current_time(void);
void	toggle_mutex(t_mtx *mutex, t_mtx_op operation);
void	print_status(t_philosopher *philo, t_state state);
void	ft_usleep(t_time time_in_ms);
bool	ft_free_bool(void *ptr, bool return_value);
bool	philo_starved(t_philosopher *philo);

/* Cleanup */
void	destroy_forks(t_simulation *sim, unsigned int num_philos);
void	destroy_mutexes(t_simulation *sim);
void	sim_cleanup(t_simulation *sim);

/* philosopher routine */
void	*philosopher_routine(void *arg);

/* sim init */
bool	create_philo_threads(t_simulation *sim);
bool	init_simulation(t_simulation *sim);

#endif
