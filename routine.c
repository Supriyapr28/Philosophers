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

static void	*handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	while (!is_dead(philo->data))
		usleep(500);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	take_forks(t_philo *philo)
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

static void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	print_status(philo, "is eating");
	precise_usleep(philo->data->time_eat, philo->data);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals++;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	philo_think(t_philo *philo)
{
	long long	think_time;

	print_status(philo, "is thinking");
	if (philo->data->n_philo % 2 != 0)
	{
		think_time = (long long)philo->data->time_eat * 2
			- philo->data->time_sleep;
		if (think_time > 0)
			precise_usleep(think_time, philo->data);
	}
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->data->n_philo == 1)
		return (handle_single_philo(philo));
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_dead(philo->data))
	{
		philo_eat(philo);
		print_status(philo, "is sleeping");
		precise_usleep(philo->data->time_sleep, philo->data);
		philo_think(philo);
	}
	return (NULL);
}
