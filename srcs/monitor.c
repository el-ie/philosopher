/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamar <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:44:14 by eamar             #+#    #+#             */
/*   Updated: 2022/08/20 17:24:34 by eamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine_monitor(void	*args)
{
	t_params	*par;

	par = args;
	usleep(50000);
	while (1)
		if (!routine_monitor_lp(par, 1, 0, 0))
			return (0);
}

int	routine_monitor_lp(t_params *par, int i, long int now, long int dt)
{
	pthread_mutex_lock(&par->global);
	while (i <= par->number_of_philosophers)
	{
		now = get_current_time();
		if (now - par->agora[i]->previous_meal > par->time_to_die * 1000)
		{
			par->alive = 0;
			pthread_mutex_unlock(&par->global);
			usleep(5000);
			pthread_mutex_lock(&par->protect_print);
			dt = (get_current_time() - par->start_time) / 1000;
			printf("%ld %d died\n", dt, i);
			pthread_mutex_unlock(&par->protect_print);
			return (0);
		}
		if (par->agora[i]->no_more_meal)
		{
			pthread_mutex_unlock(&par->global);
			return (0);
		}
		i++ ;
	}
	pthread_mutex_unlock(&par->global);
	usleep(500);
	return (1);
}
