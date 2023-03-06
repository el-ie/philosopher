/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamar <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:09:27 by eamar             #+#    #+#             */
/*   Updated: 2022/08/20 16:58:09 by eamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long int	get_current_time(void)
{
	struct timeval	current_time;
	long int		time_now;

	gettimeofday(&current_time, NULL);
	time_now = (current_time.tv_sec * 1000000) + current_time.tv_usec;
	return (time_now);
}

long int	gtp(t_philo *philo)
{
	long int	time_of_day;
	long int	time_passed;

	time_of_day = get_current_time();
	time_passed = time_of_day - philo->par->start_time;
	time_passed /= 1000;
	return (time_passed);
}

void	save_previous_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->par->global);
	philo->previous_meal = get_current_time();
	pthread_mutex_unlock(&philo->par->global);
}

void	save_starting_time(t_params *par)
{
	par->start_time = get_current_time();
}

void	little_sleep(t_philo *philo)
{
	int	dif;

	philo->last_time = get_current_time();
	dif = philo->par->time_to_eat - philo->par->time_to_sleep;
	if (dif >= 0)
		ft_sleep((dif * 1000), philo);
	ft_sleep(2000, philo);
}
