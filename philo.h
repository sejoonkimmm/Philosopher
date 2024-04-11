/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejokim <sejokim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:00:09 by sejokim           #+#    #+#             */
/*   Updated: 2023/05/30 23:37:22 by sejokim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

# define FORK_FREE	(0)
# define FORK_USED	(1)

typedef struct s_philo
{
	struct s_arg	*arg;
	pthread_t		thread;
	int				id;
	int				left;
	int				right;
	long long		last_eat_time;
	int				eat_count;
}				t_philo;

typedef struct s_arg
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				finish;
	int				finished_eat;
	long long		start_time;
	int				*fork_status;
	pthread_mutex_t	*fork_mutexes;
	pthread_mutex_t	print;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	finished_mutex;
}				t_arg;

long long	ft_atoi(char *str);
long long	actual_time(void);

void		waiting(long long wait_time, t_arg *arg);
int			print_status(t_arg *arg, int id, char *msg);
int			eating_routine(t_arg *arg, t_philo *philo);

int			init_mutex(t_arg *arg);
int			arg_init(t_arg *arg, int argc, char *argv[]);
int			philo_init(t_philo **philo, t_arg *arg);
void		first_init(t_arg *arg);

void		free_thread(t_arg *arg, t_philo *philo);
void		check_death(t_arg *arg, t_philo *philo);
void		pick_up_forks(t_arg *arg, t_philo *philo, int side);
void		put_down_forks(t_arg *arg, int side);
void		*thread(void *argv);
int			simulation_start(t_arg *arg, t_philo *philo);
int			str_is_numeric(char *str);
int			ft_isdigit(int c);
int			allocate_memory(t_arg *arg);
int			initialize_mutexes(t_arg *arg);
void		*routine(t_arg *arg, t_philo *philo);
void		philo_death(t_arg *arg, t_philo *philo, int philo_index);

#endif