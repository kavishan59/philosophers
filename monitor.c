/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkavisha <tkavisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:58:33 by tkavisha          #+#    #+#             */
/*   Updated: 2023/09/05 13:02:42 by tkavisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_var_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_dead);
	if (*philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->lock_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock_dead);
	return (0);
}

int	check_if_any_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_of_philo)
	{
		if (check_if_a_philo_dead(&philo[i]))
		{
			display(&philo[i], "died");
			pthread_mutex_lock(&philo->data->lock_dead);
			*(philo->data->dead) = 1;
			pthread_mutex_unlock(&philo->data->lock_dead);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_a_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_meal);
	if (time_now() - philo->time_last_meal >= philo->data->time_to_die
		&& !philo->eating)
	{
		pthread_mutex_unlock(&philo->data->lock_meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock_meal);
	return (0);
}

int	check_if_philos_feed(t_philo *philo)
{
	int	i;
	int	eaten_meals_needed;

	eaten_meals_needed = 0;
	if (philo->data->num_time_must_eat == -1)
		return (0);
	i = 0;
	while (i < philo->data->num_of_philo)
	{
		pthread_mutex_lock(&philo->data->lock_meal);
		if (philo[i].numb_meal_eaten >= philo->data->num_time_must_eat)
			eaten_meals_needed += 1;
		pthread_mutex_unlock(&philo->data->lock_meal);
		i++;
	}
	if (eaten_meals_needed == philo->data->num_of_philo)
	{
		pthread_mutex_lock(&philo->data->lock_dead);
		*(philo->data->dead) = 1;
		pthread_mutex_unlock(&philo->data->lock_dead);
		return (1);
	}
	return (0);
}
