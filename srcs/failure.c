/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failure.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamar <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:06:59 by eamar             #+#    #+#             */
/*   Updated: 2022/08/20 17:23:16 by eamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_error(void)
{
	write(2, "Error\n", 7);
	exit(2);
}

void	fill_agora_failure_exit(int i, t_params *par)
{
	destroy_mutexes(par);
	i--;
	while (i >= 1)
	{
		free(par->agora[i]);
		i--;
	}
	free(par->agora);
	free(par->frk);
	free(par->th);
	free(par);
	ft_error();
}

void	creation_failure(int i, t_params *par)
{
	i--;
	while (i >= 1)
	{
		pthread_join(par->th[i], NULL);
		i--;
	}
	destroy_mutexes(par);
	free_paragora(par, 1);
	ft_error();
}

void	monitoring_creation_failure(t_params *par)
{
	wait_for_threads(par);
	destroy_mutexes(par);
	free_paragora(par, 1);
	ft_error();
}
