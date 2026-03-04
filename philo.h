/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spaipur- <<spaipur-@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 10:41:25 by spaipur-          #+#    #+#             */
/*   Updated: 2026/03/04 20:52:52 by spaipur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include<limits.h>

typedef struct s_data
{
	int n_philo;
	long time_die;
	long time_eat;
	long time_sleep;
	int must_eat;
	int dead;
	long start_time;
	
	pthread_mutex_t *forks;
	pthread_mutex_t print_mutex;
	pthread_mutex_t death_mutex;	
}	t_data;

typedef struct s_philo
{
	int id;
	int meals;
	long last_meal;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_data *data;
} 	t_philo;

int parse_args(int arg_cnt, char **args, t_data *data);

#endif