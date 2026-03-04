/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <<spaipur-@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:40:50 by spaipur-          #+#    #+#             */
/*   Updated: 2026/02/12 18:35:27 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long ft_atol(const char *str)
{
	long result = 0;
	int i = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	return (result);
}

int is_number(char *str)
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

int parse_args(int arg_cnt, char **args, t_data *data)
{
	if (arg_cnt != 5 && arg_cnt != 6)
		return (1);

	while (*args)
	{
		if (!is_number(*args))
			return (1);
		args++;
	}
	data->n_philo = ft_atol(args[1]);
	data->time_die = ft_atol(args[2]);
	data->time_eat = ft_atol(args[3]);
	data->time_sleep = ft_atol(args[4]);
	data->must_eat = -1;
	if (arg_cnt == 6)
		data->must_eat = ft_atol(args[5]);
	if (data->n_philo <= 0 || data->time_die <= 0 
		|| data->time_eat <= 0 || data->time_sleep <= 0 )
		return (1);
	if (arg_cnt == 6 && data->must_eat <= 0)
		return (1);
	return (0);
}

