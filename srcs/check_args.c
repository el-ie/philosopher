/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamar <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:25:40 by eamar             #+#    #+#             */
/*   Updated: 2022/08/20 15:13:09 by eamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		ft_error();
	if (ft_longatoi(argv[1]) == 0)
		ft_error();
	if (argv[5] && ft_longatoi(argv[5]) == 0)
		exit(0);
	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '\0')
			ft_error();
		if (!only_numbers(argv[i]))
			ft_error();
		i++;
	}
	i = 1;
	while (argv[i])
	{
		if (ft_longatoi(argv[i]) > 2147483647)
			ft_error();
		i++;
	}
}

long int	ft_longatoi(char *str)
{
	long int	i;
	long int	sign;
	long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result * sign);
}

int	only_numbers(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_number(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
