/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <<spaipur-@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:41:09 by spaipur-          #+#    #+#             */
/*   Updated: 2026/03/20 22:28:49 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_data data;
	t_philo *philos;
	
	if (parse_args(ac, av + 1, &data) != 0)
		return(printf("Error: Invalid arguments\n"), 1);
	philos = malloc(sizeof(t_philo) * data.n_philo);
	if (!philos)
		return (1);
	if (init_data(&data) != 0 || init_forks(&data) != 0)
	{
		free(philos);
		return (1);
	}
	init_philos(&data, philos);
	if (create_threads(&data, philos) != 0)
	{
		cleanup(&data, philos);
		return (1);
	}
	monitor_routine(&data, philos);
	cleanup(&data, philos);
	return (0);
}
