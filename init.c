/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkavisha <tkavisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:46:15 by tkavisha          #+#    #+#             */
/*   Updated: 2023/09/05 10:56:54 by tkavisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int	init(int argc, char **argv, t_data *data, t_philo **philo)
{
	data->argc = argc;
	data->num_of_philo = (int)(ft_atoi(argv[1]));
	data->time_to_die = (int)(ft_atoi(argv[2]));
	data->time_to_eat = (int)(ft_atoi(argv[3]));
	data->time_to_sleep = (int)(ft_atoi(argv[4]));
	if (argc == 6)
		data->num_time_must_eat = (int)(ft_atoi(argv[5]));
	else
		data->num_time_must_eat = -1;
	*philo = malloc(sizeof(struct s_philo) * data->num_of_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (philo == NULL || data->forks == NULL)
	{
		free_allocated_memory(data, *philo);
		printf("Error : malloc\n");
		return (1);
	}
	if (init_mutex(data) == 1)
	{
		free_allocated_memory(data, *philo);
		return (1);
	}
	init_philo(data,*philo);
	return (0);
}

void	init_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		philo[i].data = data;
		philo[i].num = i + 1;
		philo[i].ate_enough = 0;
		philo[i].eating = 0;
		philo[i].numb_meal_eaten = 0;
		philo[i].time_last_meal = time_now();
		i++;
	}
}

void	free_allocated_memory(t_data *data, t_philo *philo)
{
	if (philo != NULL)
	{
		free(philo);
	}
	if (data->forks != NULL)
	{
		free(data->forks);
	}
}

void	destroy_failed_init_mutex(t_data *data, int until)
{
	int	i;

	pthread_mutex_destroy(&data->lock_message);
	pthread_mutex_destroy(&data->lock_dead);
	pthread_mutex_destroy(&data->lock_meal);
	i = 0;
	while (i < until)
	{
		pthread_mutex_destroy(&data->forks[i]);
	i++;
	}
}

int	init_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->lock_message, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->lock_dead, NULL) != 0)
	{
		pthread_mutex_destroy(&data->lock_message);
		return (1);
	}
	if (pthread_mutex_init(&data->lock_meal, NULL) != 0)
	{
		pthread_mutex_destroy(&data->lock_message);
		pthread_mutex_destroy(&data->lock_dead);
		return (1);
	}
	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			destroy_failed_init_mutex(data, i);
			return (1);
		}
	}
	return (0);
}
