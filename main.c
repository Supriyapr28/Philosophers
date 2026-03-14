/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <<spaipur-@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:41:09 by spaipur-          #+#    #+#             */
/*   Updated: 2026/03/14 08:59:43 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_data data;
	t_philo *philos;
	int i;
	
	if (parse_args(ac, av + 1, &data) != 0)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	philos = malloc(sizeof(t_philo) * data.n_philo);
	if (!philos)
		return (1);
	init_data(&data);
	init_forks(&data);
	init_philos(&data, philos);
	create_threads(&data, philos);
	while(1)
	{
		i = 0;
		int finish_break = 0;
		while(i < data.n_philo)
		{
			pthread_mutex_lock(&data.death_mutex);
			if (get_time_ms() - philos[i].last_meal >= data.time_die)
			{
				pthread_mutex_lock(&data.print_mutex);
				data.dead = 1;
				printf("%ld %d died\n", timestamp(&data), philos[i].id);
				pthread_mutex_unlock(&data.print_mutex);
				pthread_mutex_unlock(&data.death_mutex);
				finish_break = 1;
				return (0);
			}
			pthread_mutex_unlock(&data.death_mutex);
			i++;
		}
		if (finish_break)
			break ;
		usleep(1000);
	}
	i = 0;
	while (i < data.n_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data.n_philo)
	{
		pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data.print_mutex);
	pthread_mutex_destroy(&data.death_mutex);
	free(data.forks);
	free(philos);
	return (0);
}