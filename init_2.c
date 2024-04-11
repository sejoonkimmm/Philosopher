/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejokim <sejokim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 22:47:37 by sejokim           #+#    #+#             */
/*   Updated: 2023/05/30 23:38:18 by sejokim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	first_init(t_arg *arg)
{
	arg->philo_num = 0;
	arg->time_to_die = 0;
	arg->time_to_eat = 0;
	arg->time_to_sleep = 0;
	arg->must_eat = 0;
	arg->start_time = 0;
	arg->finished_eat = 0;
	arg->finish = 0;
	arg->fork_mutexes = NULL;
	arg->fork_status = NULL;
}

void	free_thread(t_arg *arg, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < arg->philo_num)
		pthread_mutex_destroy(&(arg->fork_mutexes[i++]));
	free(philo);
	free(arg->fork_status);
	free(arg->fork_mutexes);
	pthread_mutex_destroy(&(arg->print));
	pthread_mutex_destroy(&(arg->eat_mutex));
	pthread_mutex_destroy(&(arg->finished_mutex));
}
