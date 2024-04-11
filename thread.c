/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejokim <sejokim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 23:27:05 by sejokim           #+#    #+#             */
/*   Updated: 2023/05/30 23:37:30 by sejokim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(t_arg *arg, t_philo *philo)
{
	eating_routine(arg, philo);
	pthread_mutex_lock(&(arg->eat_mutex));
	if (arg->must_eat == philo->eat_count)
	{
		arg->finished_eat++;
		pthread_mutex_unlock(&(arg->eat_mutex));
		return ((void *)1);
	}
	pthread_mutex_unlock(&(arg->eat_mutex));
	print_status(arg, philo->id, "is sleeping");
	waiting((long long)arg->time_to_sleep, arg);
	print_status(arg, philo->id, "is thinking");
	return (0);
}

void	*thread(void *argv)
{
	t_arg		*arg;
	t_philo		*philo;
	int			finish;

	philo = argv;
	arg = philo->arg;
	if (philo->id % 2)
		usleep(1000);
	else
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&(arg->finished_mutex));
		finish = arg->finish;
		pthread_mutex_unlock(&(arg->finished_mutex));
		if (finish)
			break ;
		if (routine(arg, philo) == (void *)1)
			break ;
	}
	return (0);
}
