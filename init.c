/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <<spaipur-@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:41:15 by spaipur-          #+#    #+#             */
/*   Updated: 2026/02/12 19:12:47 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_data(t_data *data)
{
	data->dead = 0;
	data->start_time = 0;
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->death_mutex, NULL))
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
		return (1);
	return (0);
}

int init_forks(t_data *data)
{
	int i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

void init_philos(t_data *data, t_philo *philos)
{
	int i = 0;
	while (i < data->n_philo)
	{
		philos[i].id = i + 1;
		philos[i].meals = 0;
		philos[i].last_meal = 0;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->n_philo];
		philos[i].data = data;
		i++;
	}
}

int create_threads(t_data *data, t_philo *philos)
{
	int i;
	
	i = 0;
	data->start_time = get_time_ms();
	while (i < data->n_philo)
	{
		philos[i].last_meal = data->start_time;
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}