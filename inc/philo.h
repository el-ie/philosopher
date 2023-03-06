/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamar <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:44:03 by eamar             #+#    #+#             */
/*   Updated: 2022/08/20 17:10:19 by eamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <errno.h>
# include <string.h>
# include <pthread.h>

# define NOLOCK 0
# define LOCKED 1
# define THINKING 0
# define TAKE_FORK 1
# define EAT 2
# define SLEEP 3
# define TAKE_FORK_AND_EAT 4
# define DEBUG 0

typedef struct s_params
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_time_each_philosopher_must_eat;
	int				eat_limit_status;
	int				alive;
	long int		start_time;
	pthread_t		*th;
	struct s_philo	**agora;
	pthread_mutex_t	*frk;
	pthread_mutex_t	protect_print;
	pthread_mutex_t	global;
}	t_params;

typedef struct s_philo
{
	t_params	*par;
	int			index;
	int			fork_a;
	int			fork_b;
	int			count;
	int			end;
	int			no_more_meal;
	long int	last_time;
	long int	previous_meal;
}	t_philo;

int			only_numbers(char *str);
int			is_number(char c);
int			routine_monitor_lp(t_params *par, int i, long int now, long int dt);
int			other_fork(int index, t_philo *philo);
int			is_even(t_philo *philo);
int			routine_loop(t_philo *philo, int number_of_philosophers);
int			check_if_someone_died(t_philo *philo, int mutex_locked);
int			no_other_meal(t_philo *philo);
void		check_args(int argc, char **argv);
void		ft_error(void);
void		fill_agora_failure_exit(int i, t_params *par);
void		creation_failure(int i, t_params *par);
void		monitoring_creation_failure(t_params *par);
void		manage_eat_limit(t_params *par, char **argv);
void		init_mutexes(t_params *par);
void		init_mutexes_destroy_last_frk(int i, t_params *par);
void		init_parameters_frexit(t_params *par, int option);
void		fill_agora(t_params *par);
void		free_paragora(t_params *par, int philos_created);
void		wait_for_threads(t_params *par);
void		destroy_mutexes(t_params *par);
void		print_message(int action, t_philo *philo);
void		printf_protected(char *str, t_philo *philo);
void		ft_swap(int *fork_a, int *fork_b);
void		ft_sleep(int wait_time, t_philo *philo);
void		save_previous_meal(t_philo *philo);
void		save_starting_time(t_params *par);
void		*routine(void *args);
void		little_sleep(t_philo *philo);
void		*routine_monitor(void *args);
long int	ft_longatoi(char *str);
long int	get_current_time(void);
long int	gtp(t_philo *philo);
t_params	*init_parameters(char **argv);
t_philo		*new_philo(int i, t_params *par, long int now);

#endif
