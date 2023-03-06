/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamar <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:11:30 by eamar             #+#    #+#             */
/*   Updated: 2022/08/20 15:13:54 by eamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	*new_philo(int i, t_params *par, long int now)
{
	t_philo	*obj;

	obj = malloc(sizeof(t_philo));
	if (!obj)
		return (0);
	obj->index = i;
	obj->fork_a = i;
	if (i != par->number_of_philosophers)
		obj->fork_b = i + 1;
	else
		obj->fork_b = 1;
	obj->par = par;
	if (i % 2 == 0)
		ft_swap(&obj->fork_a, &obj->fork_b);
	obj->previous_meal = now;
	obj->count = 0;
	obj->end = 0;
	obj->no_more_meal = 0;
	return (obj);
}

void	fill_agora(t_params *par)
{
	long int	now;
	int			i;

	now = get_current_time();
	i = 1;
	while (i <= par->number_of_philosophers)
	{
		par->agora[i] = new_philo(i, par, now);
		if (!par->agora[i])
			fill_agora_failure_exit(i, par);
		i++;
	}
}

void	free_paragora(t_params *par, int philos_created)
{
	int	i;

	i = 1;
	if (philos_created)
	{
		while (i <= par->number_of_philosophers)
		{
			free(par->agora[i]);
			i++;
		}
	}
	free(par->agora);
	free(par->frk);
	free(par->th);
	free(par);
}

void	wait_for_threads(t_params *par)
{
	int	i;

	i = 1;
	while (i <= par->number_of_philosophers)
	{
		pthread_join(par->th[i], NULL);
		i++;
	}
}

void	destroy_mutexes(t_params *par)
{
	int	i;

	i = 1;
	while (i <= par->number_of_philosophers)
	{
		pthread_mutex_destroy(&(par->frk[i]));
		i++;
	}
	pthread_mutex_destroy(&(par->protect_print));
	pthread_mutex_destroy(&(par->global));
}
