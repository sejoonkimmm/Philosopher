/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejokim <sejokim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:59:40 by sejokim           #+#    #+#             */
/*   Updated: 2023/05/30 23:38:16 by sejokim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_memory(t_arg *arg)
{
	arg->fork_status = malloc(sizeof(int) * arg->philo_num);
	if (!(arg->fork_status))
		return (1);
	arg->fork_mutexes = malloc(sizeof(pthread_mutex_t) * arg->philo_num);
	if (!(arg->fork_mutexes))
	{
		free(arg->fork_status);
		return (1);
	}
	return (0);
}

int	initialize_mutexes(t_arg *arg)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(arg->print), NULL))
		return (1);
	if (pthread_mutex_init(&(arg->eat_mutex), NULL))
		return (1);
	if (pthread_mutex_init(&(arg->finished_mutex), NULL))
		return (1);
	while (i < arg->philo_num)
	{
		arg->fork_status[i] = 0;
		if (pthread_mutex_init(&(arg->fork_mutexes[i]), NULL))
		{
			free(arg->fork_status);
			free(arg->fork_mutexes);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_mutex(t_arg *arg)
{
	if (allocate_memory(arg))
		return (1);
	if (initialize_mutexes(arg))
		return (1);
	return (0);
}

int	arg_init(t_arg *arg, int argc, char *argv[])
{
	if (!str_is_numeric(argv[1]) || !str_is_numeric(argv[2]) || \
		!str_is_numeric(argv[3]) || !str_is_numeric(argv[4]) || \
		argv == NULL)
		return (1);
	arg->philo_num = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	arg->start_time = actual_time();
	if (arg->philo_num <= 0 || arg->time_to_die <= 0 || arg->time_to_eat <= 0 \
		|| arg->time_to_sleep <= 0)
		return (1);
	if (argc == 6)
	{
		if (!str_is_numeric(argv[5]) || arg->philo_num == 1)
			return (1);
		arg->must_eat = ft_atoi(argv[5]);
		if (arg->must_eat <= 0)
			return (1);
	}
	if (init_mutex(arg))
		return (1);
	return (0);
}

int	philo_init(t_philo **philo, t_arg *arg)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * arg->philo_num);
	if (!(philo))
		return (1);
	while (i < arg->philo_num)
	{
		(*philo)[i].arg = arg;
		(*philo)[i].id = i;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % arg->philo_num;
		(*philo)[i].last_eat_time = actual_time();
		(*philo)[i].eat_count = 0;
		i++;
	}
	return (0);
}
