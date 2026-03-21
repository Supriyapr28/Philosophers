/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <<spaipur-@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 10:41:25 by spaipur-          #+#    #+#             */
/*   Updated: 2026/03/21 18:37:07 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_data
{
	int				n_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				must_eat;
	int				dead;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;	
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal;
	int				meals;
	pthread_mutex_t	meal_lock;
	t_data			*data;
}	t_philo;

/* Init functions */
int		init_data(t_data *data);
int		init_forks(t_data *data);
int		create_threads(t_data *data, t_philo *philos);
void	init_philos(t_data *data, t_philo *philos);
void	cleanup(t_data *data, t_philo *philos);

/* Utils */
int		parse_args(int arg_cnt, char **args, t_data *data);
void	*philo_routine(void *arg);
long	get_time_ms(void);
long	timestamp(t_data *data);
void	precise_usleep(long time_in_ms, t_data *data);
void	monitor_routine(t_data *data, t_philo *philos);
int		is_dead(t_data *data);	
void	take_forks(t_philo *philo);
void	print_status(t_philo *philo, char *status);
#endif