/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkavisha <tkavisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:35:23 by tkavisha          #+#    #+#             */
/*   Updated: 2023/09/03 15:37:24 by tkavisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	if (argc != 6 && argc != 5)
	{
		write(1, "Error : Wrong number of arguments\n", 34);
		return (1);
	}
	if (check_if_args_null(argv) == 1)
	{
		write(1, "Error: Contains null arguments\n", 32);
		return (1);
	}
	if (check_if_args_valid_numbers(argv) == 1)
	{
		write(1, "Error: Contains invalid arguments\n", 34);
		return (1);
	}
	if (check_if_args_max(argv) == 1)
	{
		write(1, "Error: value > MAX_INT\n", 23);
		return (1);
	}
	return (0);
}

int	check_if_args_null(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_if_args_valid_numbers(char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (ft_atoi(argv[1]) == 0)
	{
		return (1);
	}
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_if_args_max(char **argv)
{
	unsigned long long	number;
	int					i;

	i = 1;
	while (argv[i])
	{
		number = ft_atoi(argv[i]);
		if (number > 2147483647)
			return (1);
		i++;
	}
	return (0);
}
