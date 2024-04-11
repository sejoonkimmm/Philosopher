/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejokim <sejokim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:59:48 by sejokim           #+#    #+#             */
/*   Updated: 2023/05/30 23:38:24 by sejokim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiting(long long wait_time, t_arg *arg)
{
	long long	start_time;
	long long	present;

	start_time = actual_time();
	while (1)
	{
		pthread_mutex_lock(&(arg->finished_mutex));
		if (arg->finish)
		{
			pthread_mutex_unlock(&(arg->finished_mutex));
			break ;
		}
		pthread_mutex_unlock(&(arg->finished_mutex));
		present = actual_time();
		if ((present - start_time) >= wait_time)
			break ;
		usleep(1000);
	}
}

int	print_status(t_arg *arg, int id, char *msg)
{
	long long	present;

	present = actual_time();
	if (present == -1)
	{
		return (-1);
	}
	if (!(arg->finish))
	{
		pthread_mutex_lock(&(arg->print));
		printf("%lld %d %s\n", present - arg->start_time, id + 1, msg);
		pthread_mutex_unlock(&(arg->print));
	}
	return (0);
}

void	pick_up_forks(t_arg *arg, t_philo *philo, int side)
{
	pthread_mutex_lock(&(arg->fork_mutexes[side]));
	while (arg->fork_status[side] == FORK_USED)
	{
		pthread_mutex_unlock(&(arg->fork_mutexes[side]));
		usleep(100);
		pthread_mutex_lock(&(arg->fork_mutexes[side]));
	}
	arg->fork_status[side] = FORK_USED;
	print_status(arg, philo->id, "has taken a fork");
}

void	put_down_forks(t_arg *arg, int side)
{
	arg->fork_status[side] = FORK_FREE;
	pthread_mutex_unlock(&(arg->fork_mutexes[side]));
}

int	eating_routine(t_arg *arg, t_philo *philo)
{
	pick_up_forks(arg, philo, philo->left);
	if (arg->philo_num != 1)
	{
		pick_up_forks(arg, philo, philo->right);
		pthread_mutex_lock(&(arg->eat_mutex));
		philo->last_eat_time = actual_time();
		print_status(arg, philo->id, "is eating");
		philo->eat_count = philo->eat_count + 1;
		pthread_mutex_unlock(&(arg->eat_mutex));
		waiting((long long)arg->time_to_eat, arg);
		put_down_forks(arg, philo->right);
	}
	put_down_forks(arg, philo->left);
	return (0);
}
