/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <<spaipur-@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:41:09 by spaipur-          #+#    #+#             */
/*   Updated: 2026/03/23 10:44:35 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (data->forks)
		free(data->forks);
}

long	ft_atol(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	return (result);
}

int	is_number(char *str)
{
	if (!str || str[0] == '\0')
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	parse_args(int arg_cnt, char **args, t_data *data)
{
	int	i;

	if (arg_cnt != 5 && arg_cnt != 6)
		return (1);
	i = 0;
	while (args[i])
	{
		if (!is_number(args[i]))
			return (1);
		i++;
	}
	data->n_philo = ft_atol(args[0]);
	data->time_die = ft_atol(args[1]);
	data->time_eat = ft_atol(args[2]);
	data->time_sleep = ft_atol(args[3]);
	data->must_eat = -1;
	if (arg_cnt == 6)
		data->must_eat = ft_atol(args[4]);
	if (data->n_philo <= 0 || data->time_die <= 0 || data->time_eat <= 0
		|| data->time_sleep <= 0)
		return (1);
	if (arg_cnt == 6 && data->must_eat <= 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	if (parse_args(ac, av + 1, &data) != 0)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
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
