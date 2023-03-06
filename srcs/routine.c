/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamar <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:40:58 by eamar             #+#    #+#             */
/*   Updated: 2022/08/20 19:36:03 by eamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void	*args)
{
	t_philo		*philo;
	int			number_of_philosophers;

	philo = args;
	number_of_philosophers = philo->par->number_of_philosophers;
	if (philo->index % 2 == 0)
		usleep(5000);
	save_previous_meal(philo);
	while (1)
		if (!routine_loop(philo, number_of_philosophers))
			return (0);
}

int	routine_loop(t_philo *philo, int number_of_philosophers)
{
	if (check_if_someone_died(philo, NOLOCK))
		return (0);
	print_message(THINKING, philo);
	little_sleep(philo);
	if (number_of_philosophers == 1)
		return (0);
	pthread_mutex_lock(&philo->par->frk[philo->fork_a]);
	print_message(TAKE_FORK, philo);
	pthread_mutex_lock(&philo->par->frk[philo->fork_b]);
	philo->last_time = get_current_time();
	save_previous_meal(philo);
	if (check_if_someone_died(philo, LOCKED))
		return (0);
	print_message(TAKE_FORK_AND_EAT, philo);
	ft_sleep(philo->par->time_to_eat * 1000, philo);
	philo->last_time = get_current_time();
	pthread_mutex_unlock(&philo->par->frk[philo->fork_b]);
	pthread_mutex_unlock(&philo->par->frk[philo->fork_a]);
	if (no_other_meal(philo))
		return (0);
	if (check_if_someone_died(philo, NOLOCK))
		return (0);
	print_message(SLEEP, philo);
	ft_sleep(philo->par->time_to_sleep * 1000, philo);
	return (1);
}

void	ft_sleep(int wait_time, t_philo *philo)
{
	while (1)
	{
		usleep(500);
		pthread_mutex_lock(&philo->par->global);
		if (!philo->par->alive)
		{
			pthread_mutex_unlock(&philo->par->global);
			return ;
		}
		pthread_mutex_unlock(&philo->par->global);
		if (get_current_time() - philo->last_time >= wait_time)
			return ;
	}
}

int	check_if_someone_died(t_philo *philo, int mutex_locked)
{
	pthread_mutex_lock(&philo->par->global);
	if (philo->par->alive == 0)
	{
		pthread_mutex_unlock(&philo->par->global);
		if (mutex_locked)
		{
			pthread_mutex_unlock(&philo->par->frk[philo->fork_b]);
			pthread_mutex_unlock(&philo->par->frk[philo->fork_a]);
		}
		return (1);
	}
	pthread_mutex_unlock(&philo->par->global);
	return (0);
}

int	no_other_meal(t_philo *philo)
{
	philo->count++;
	pthread_mutex_lock(&philo->par->global);
	if (!philo->par->eat_limit_status)
	{
		pthread_mutex_unlock(&philo->par->global);
		return (0);
	}
	if (philo->count == philo->par->number_of_time_each_philosopher_must_eat)
	{
		philo->no_more_meal = 1;
		pthread_mutex_unlock(&philo->par->global);
		return (1);
	}
	pthread_mutex_unlock(&philo->par->global);
	return (0);
}
