/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <<spaipur-@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:41:15 by spaipur-          #+#    #+#             */
/*   Updated: 2026/03/21 18:22:26 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data)
{
	data->dead = 0;
	data->start_time = 0;
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->death_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->meal_mutex, NULL))
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
		return (1);
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

void	init_philos(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		philos[i].id = i + 1;
		philos[i].meals = 0;
		philos[i].last_meal = 0;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->n_philo];
		philos[i].data = data;
		pthread_mutex_init(&philos[i].meal_lock, NULL);
		i++;
	}
}

int	create_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	data->start_time = get_time_ms();
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&philos[i].meal_lock);
		philos[i].last_meal = data->start_time;
		pthread_mutex_unlock(&philos[i].meal_lock);
		if (pthread_create(&philos[i].thread, NULL, philo_routine,
				&philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	cleanup(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	if (philos)
	{
		while (i < data->n_philo)
		{
			pthread_join(philos[i].thread, NULL);
			i++;
		}
		i = 0;
		while (i < data->n_philo)
		{
			pthread_mutex_destroy(&data->forks[i]);
			pthread_mutex_destroy(&philos[i].meal_lock);
			i++;
		}
		free(philos);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	if (data->forks)
		free(data->forks);
}
