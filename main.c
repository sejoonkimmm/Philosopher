/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejokim <sejokim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:59:36 by sejokim           #+#    #+#             */
/*   Updated: 2023/05/30 23:37:20 by sejokim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_start(t_arg *arg, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < arg->philo_num)
	{	
		philo[i].last_eat_time = actual_time();
		if (pthread_create(&(philo[i].thread), NULL, thread, &(philo[i])))
			return (1);
		i++;
	}
	check_death(arg, philo);
	i = 0;
	while (i < arg->philo_num)
		pthread_join(philo[i++].thread, NULL);
	free_thread(arg, philo);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_arg	arg;
	t_philo	*philo;

	first_init(&arg);
	if (arg_init(&arg, argc, argv) || (argc != 5 && argc != 6))
		return (!printf("Wrong Arguments.\n"));
	if (philo_init(&philo, &arg))
		return (!printf("Philo init failed.\n"));
	if (simulation_start(&arg, philo))
		return (!printf("Failed to simulation start.\n"));
	return (0);
}
