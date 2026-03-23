/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <<spaipur-@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:40:43 by spaipur-          #+#    #+#             */
/*   Updated: 2026/03/23 10:42:57 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	precise_usleep(long time_in_ms, t_data *data)
{
	long	start_time;

	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < time_in_ms)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->death_mutex);
		usleep(500);
	}
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	timestamp(t_data *data)
{
	return (get_time_ms() - data->start_time);
}
