/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkavisha <tkavisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:08:05 by tkavisha          #+#    #+#             */
/*   Updated: 2023/09/05 03:54:53 by tkavisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	philo_sleep(t_philo *philo)
{
	display(philo, "is sleeping");
	my_usleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	display(philo, "is thinking");
}

void	philo_eat2(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_meal);
	philo->time_last_meal = time_now();
	pthread_mutex_unlock(&philo->data->lock_meal);
	my_usleep(philo->data->time_to_eat);
	philo->eating = 0;
	pthread_mutex_lock(&philo->data->lock_meal);
	philo->numb_meal_eaten += 1;
	pthread_mutex_unlock(&philo->data->lock_meal);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->num - 1]);
	display(philo, "has taken a fork");
	if (philo->data->num_of_philo == 1)
	{
		my_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(&philo->data->forks[philo->num - 1]);
		return ;
	}
	if (philo->num == 1)
		pthread_mutex_lock(&philo->data->forks[philo->data->num_of_philo - 1]);
	else
		pthread_mutex_lock(&philo->data->forks[philo->num - 2]);
	display(philo, "has taken a fork");
	philo->eating = 1;
	display(philo, "is eating");
	philo_eat2(philo);
	if (philo->num == 1)
		pthread_mutex_unlock(
			&philo->data->forks[philo->data->num_of_philo - 1]);
	else
		pthread_mutex_unlock(&philo->data->forks[philo->num - 2]);
	pthread_mutex_unlock(&philo->data->forks[philo->num - 1]);
}
