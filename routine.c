/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <<spaipur-@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:40:58 by spaipur-          #+#    #+#             */
/*   Updated: 2026/03/14 08:41:51 by spaipur-         ###   ########.fr       */
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
        usleep(philo->data->time_eat * 1000);

        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

        philo->meals++;

        print_status(philo, "is sleeping");
        usleep(philo->data->time_sleep * 1000);

        print_status(philo, "is thinking");
    }
    return (NULL);
}