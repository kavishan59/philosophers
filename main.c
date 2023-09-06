/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkavisha <tkavisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:58:26 by tkavisha          #+#    #+#             */
/*   Updated: 2023/09/05 13:15:51 by tkavisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>

void	display(t_philo *philo, char *s)
{
	u_int64_t	timestamp;

	pthread_mutex_lock(&philo->data->lock_message);
	timestamp = time_now() - philo->data->start;
	if (check_var_dead(philo) == 0)
	{
		printf("%lu %d %s\n", timestamp, philo->num, s);
	}
	pthread_mutex_unlock(&philo->data->lock_message);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	int		dead;

	data.start = time_now();
	dead = 0;
	data.dead = &dead;
	if (check_args(argc, argv) == 1)
		return (1);
	if (init(argc, argv, &data, &philo) == 1)
		return (1);
	if (create_threads(&data, philo) == 1)
		return (1);
	join_threads(&data, philo);
	clean_mutex(philo);
	free_allocated_memory(&data, philo);
	return (0);
}
