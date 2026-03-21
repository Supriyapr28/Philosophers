/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <<spaipur-@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 18:00:00 by spaipur-          #+#    #+#             */
/*   Updated: 2026/03/21 18:53:09 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_lock(&philos[i].meal_lock);
		if ((get_time_ms() - philos[i].last_meal) >= data->time_die)
		{
			pthread_mutex_unlock(&philos[i].meal_lock);
			print_status(&philos[i], "died");
			pthread_mutex_lock(&data->death_mutex);
			data->dead = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philos[i].meal_lock);
	}
	return (0);
}

static int	check_meals(t_data *data, t_philo *philos)
{
	int	i;
	int	all_ate;

	i = -1;
	all_ate = 1;
	if (data->must_eat == -1)
		return (0);
	while (++i < data->n_philo)
	{
		pthread_mutex_lock(&philos[i].meal_lock);
		if (philos[i].meals < data->must_eat)
			all_ate = 0;
		pthread_mutex_unlock(&philos[i].meal_lock);
	}
	if (all_ate)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->dead = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

void	monitor_routine(t_data *data, t_philo *philos)
{
	while (1)
	{
		if (check_death(data, philos) || check_meals(data, philos))
			return ;
		usleep(1000);
	}
}
