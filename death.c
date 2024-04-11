/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejokim <sejokim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 23:27:23 by sejokim           #+#    #+#             */
/*   Updated: 2023/05/30 23:37:11 by sejokim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_death(t_arg *arg, t_philo *philo, int philo_index)
{
	long long	present;
	long long	last_eat_time_temp;

	present = actual_time();
	pthread_mutex_lock(&(arg->eat_mutex));
	last_eat_time_temp = philo[philo_index].last_eat_time;
	pthread_mutex_unlock(&(arg->eat_mutex));
	if ((present - last_eat_time_temp) >= arg->time_to_die)
	{
		pthread_mutex_lock(&(arg->finished_mutex));
		print_status(arg, philo_index, "died");
		arg->finish = 1;
		pthread_mutex_unlock(&(arg->finished_mutex));
	}
}

void	check_death(t_arg *arg, t_philo *philo)
{
	int	i;

	while (!arg->must_eat && !arg->finish)
	{
		i = 0;
		while (i < arg->philo_num)
		{
			philo_death(arg, philo, i);
			i++;
		}
	}
}
