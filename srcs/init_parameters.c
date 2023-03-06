/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parameters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamar <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:26:07 by eamar             #+#    #+#             */
/*   Updated: 2022/08/20 15:13:31 by eamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_params	*init_parameters(char **argv)
{
	t_params	*par;
	int			mutex_size;

	mutex_size = sizeof(pthread_mutex_t);
	par = malloc(sizeof(t_params));
	if (!par)
		ft_error();
	par->alive = 1;
	par->number_of_philosophers = ft_longatoi(argv[1]);
	par->time_to_die = ft_longatoi(argv[2]);
	par->time_to_eat = ft_longatoi(argv[3]);
	par->time_to_sleep = ft_longatoi(argv[4]);
	manage_eat_limit(par, argv);
	par->agora = malloc(sizeof(t_philo *) * (par->number_of_philosophers + 1));
	if (!par->agora)
		init_parameters_frexit(par, 1);
	par->frk = malloc(mutex_size * (par->number_of_philosophers + 1));
	if (!par->frk)
		init_parameters_frexit(par, 2);
	par->th = malloc(sizeof(pthread_t) * (par->number_of_philosophers + 1));
	if (!par->th)
		init_parameters_frexit(par, 3);
	init_mutexes(par);
	return (par);
}

void	manage_eat_limit(t_params *par, char **argv)
{
	if (argv[5])
	{
		par->number_of_time_each_philosopher_must_eat = ft_longatoi(argv[5]);
		par->eat_limit_status = 1;
	}
	else
	{
		par->eat_limit_status = 0;
		par->number_of_time_each_philosopher_must_eat = 0;
	}
}

void	init_mutexes(t_params *par)
{
	static int	i = 1;

	while (i <= par->number_of_philosophers)
	{
		if (pthread_mutex_init(&(par->frk[i]), NULL) != 0)
		{
			init_mutexes_destroy_last_frk(i, par);
			free_paragora(par, 0);
			ft_error();
		}
		i++;
	}
	if (pthread_mutex_init(&(par->protect_print), NULL) != 0)
	{
		init_mutexes_destroy_last_frk(par->number_of_philosophers, par);
		free_paragora(par, 0);
		ft_error();
	}
	if (pthread_mutex_init(&(par->global), NULL) != 0)
	{
		init_mutexes_destroy_last_frk(par->number_of_philosophers, par);
		pthread_mutex_destroy(&(par->protect_print));
		free_paragora(par, 0);
		ft_error();
	}
}

void	init_mutexes_destroy_last_frk(int i, t_params *par)
{
	i--;
	while (i >= 1)
	{
		pthread_mutex_destroy(&(par->frk[i]));
		i--;
	}
}

void	init_parameters_frexit(t_params *par, int option)
{
	if (option >= 2)
		free(par->agora);
	if (option >= 3)
		free(par->frk);
	free(par);
	ft_error();
}
