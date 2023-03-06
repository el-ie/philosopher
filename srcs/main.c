/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamar <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:15:53 by eamar             #+#    #+#             */
/*   Updated: 2022/08/20 17:26:02 by eamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_params	*par;
	pthread_t	monitoring;
	int			i;

	check_args(argc, argv);
	par = init_parameters(argv);
	fill_agora(par);
	save_starting_time(par);
	i = 1;
	while (i <= par->number_of_philosophers)
	{
		if (pthread_create(&par->th[i], NULL, &routine, par->agora[i]) != 0)
			creation_failure(i, par);
		i++;
	}
	if (pthread_create(&monitoring, NULL, &routine_monitor, par) != 0)
		monitoring_creation_failure(par);
	wait_for_threads(par);
	pthread_join(monitoring, NULL);
	destroy_mutexes(par);
	free_paragora(par, 1);
	return (0);
}
