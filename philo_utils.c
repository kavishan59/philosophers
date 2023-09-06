/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkavisha <tkavisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:15:59 by tkavisha          #+#    #+#             */
/*   Updated: 2023/09/05 14:00:16 by tkavisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	ft_strlen( char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

unsigned long long	ft_atoi(char *s)
{
	int					i;
	unsigned long long	result;

	result = 0;
	i = 0;
	if (s[0] == '+')
		i++;
	while (i < ft_strlen(s))
	{
		result = result * 10 + s[i] - 48;
		i++;
	}
	return (result);
}

void	clean_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_of_philo)
	{
		pthread_mutex_destroy(&philo->data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->data->lock_dead);
	pthread_mutex_destroy(&philo->data->lock_meal);
	pthread_mutex_destroy(&philo->data->lock_message);
}

u_int64_t	time_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeoftoday error\n", 20);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	my_usleep(u_int64_t time)
{
	u_int64_t	i;

	i = time_now();
	while (time_now() - i < time)
		usleep(500);
}
