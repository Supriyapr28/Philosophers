/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- 	<spaipur-@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:40:58 by spaipur-          #+#    #+#             */
/*   Updated: 2026/03/20 22:21:11 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_status(t_philo *philo, char *status)
{

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->dead)
		printf("%ld %d %s\n", timestamp(philo->data), philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
}

void *philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->data->dead)
    {
        take_forks(philo);
        pthread_mutex_lock(&philo->data->death_mutex);
        philo->last_meal = get_time_ms();
        pthread_mutex_unlock(&philo->data->death_mutex);
        print_status(philo, "is eating");
		precise_usleep(philo->data->time_eat, philo->data);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        philo->meals++;
        print_status(philo, "is sleeping");
		precise_usleep(philo->data->time_sleep, philo->data);
        print_status(philo, "is thinking");
    }
    return (NULL);
}

// static int check_must_eat(t_data *data, t_philo *philos)
// {
// 	int i;
// 	int finished_eating;;

// 	if (data->must_eat == -1)
// 		return (0);
// 	i = 0;
// 	finished_eating = 0;
// 	while (i < data->n_philo)
// 	{
// 		pthread_mutex_lock(&data->death_mutex);
// 		if (philos[i].meals >= data->must_eat)
// 			finished_eating++;
// 		pthread_mutex_unlock(&data->death_mutex);
// 		i++;
// 	}
// 	if (finished_eating >= data->n_philo)
// 	{
// 		pthread_mutex_lock(&data->death_mutex);
// 		data->dead = 1;
// 		pthread_mutex_unlock(&data->death_mutex);
// 		return (1);
// 	}															
// 	return (0);
// }

void *monitor_routine(t_data *data, t_philo *philos)
{
	int i;
	while(1)
	{
		i = -1;
		while(++i < data->n_philo)
		{
			pthread_mutex_lock(&data->death_mutex);
			if ((get_time_ms() - philos[i].last_meal) >= data->time_die)
			{
				print_status(&philos[i], "died");
				data->dead = 1;
				pthread_mutex_unlock(&data->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->death_mutex);
		}
		// if (check_must_eat(data, philos))
		// 		return;
		usleep(1000);
	}
}
