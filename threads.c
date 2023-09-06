/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkavisha <tkavisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:49:38 by tkavisha          #+#    #+#             */
/*   Updated: 2023/09/05 18:06:31 by tkavisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	if (pthread_create(&data->threads_monitor_tid,
			NULL, &threads_monitor, philo) != 0)
	{
		printf("Error : pthread_create");
		clean_mutex(philo);
		free_allocated_memory(data, philo);
		return (1);
	}
	while (i < data->num_of_philo)
	{
		if (pthread_create(&philo[i].tid, NULL, &philo_routine, &philo[i]) != 0)
		{
			printf("Error : pthread_create");
			create_threads_error(data, philo, i);
			clean_mutex(philo);
			free_allocated_memory(data, philo);
			return (1);
		}
		i++;
	}
	return (0);
}

void	create_threads_error(t_data *data, t_philo *philo, int until)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->lock_dead);
	*(data->dead) = 1;
	pthread_mutex_unlock(&data->lock_dead);
	while (i < until)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
}

void	*threads_monitor(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	while (1)
	{
		if (check_if_any_dead(philo) == 1 || check_if_philos_feed(philo) == 1)
			break ;
	}
	return (NULL);
}

void	join_threads(t_data *data, t_philo *philo)
{
	int	i;

	if (pthread_join(data->threads_monitor_tid, NULL) != 0)
		write(2, "Thread join error\n", 18);
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_join(philo[i].tid, NULL) != 0)
			write(2, "Thread join error\n", 18);
		i++;
	}
}

void	*philo_routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	if (philo->num % 2 == 0)
		my_usleep(1);
	while (check_var_dead(philo) == 0)
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
