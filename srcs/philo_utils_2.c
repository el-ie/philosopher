/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamar <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:14:20 by eamar             #+#    #+#             */
/*   Updated: 2022/08/20 17:19:53 by eamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_message(int action, t_philo *philo)
{
	if (DEBUG == 1)
	{
		return ;
	}
	if (action == THINKING)
		printf_protected("%ld %d is thinking\n", philo);
	else if (action == TAKE_FORK)
		printf_protected("%ld %d has taken a fork\n", philo);
	else if (action == EAT)
		printf_protected("%ld %d is eating\n", philo);
	else if (action == SLEEP)
		printf_protected("%ld %d is sleeping\n", philo);
	else if (action == TAKE_FORK_AND_EAT)
	{
		printf_protected("%ld %d has taken a fork\n", philo);
		printf_protected("%ld %d is eating\n", philo);
	}
}

void	printf_protected(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->par->protect_print);
	printf(str, gtp(philo), philo->index);
	pthread_mutex_unlock(&philo->par->protect_print);
}

int	other_fork(int index, t_philo *philo)
{
	int	philosophers;

	philosophers = philo->par->number_of_philosophers;
	if (index == philosophers)
		return (1);
	else
		return (index + 1);
}

int	is_even(t_philo *philo)
{
	if (philo->par->number_of_philosophers % 2 == 0)
		return (1);
	return (0);
}

void	ft_swap(int *fork_a, int *fork_b)
{
	int	tmp;

	tmp = *fork_a;
	*fork_a = *fork_b;
	*fork_b = tmp;
}
