/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkavisha <tkavisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:12:02 by tkavisha          #+#    #+#             */
/*   Updated: 2023/09/05 17:52:07 by tkavisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <bits/types/struct_timeval.h>
# include <pthread.h>
# include <sys/types.h>
# include <time.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_data
{
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	u_int64_t		start;
	int				num_of_philo;
	int				num_time_must_eat;
	int				*dead;
	int				argc;
	pthread_mutex_t	lock_message;
	pthread_mutex_t	lock_dead;
	pthread_mutex_t	lock_meal;
	pthread_mutex_t	*forks;
	pthread_t		threads_monitor_tid;
}	t_data;

typedef struct s_philo
{
	int			num;
	int			eating;
	int			ate_enough;
	int			numb_meal_eaten;
	u_int64_t	time_last_meal;
	pthread_t	tid;
	t_data		*data;
}	t_philo;

int					ft_strlen(char *s);
int					check_if_args_null(char **argv);
int					check_if_args_valid_numbers(char **argv);
unsigned long long	ft_atoi(char *s);
int					check_if_args_max(char **argv);
int					check_args(int argc, char **argv);
int					init(int argc, char **argv, t_data *data, t_philo **philo);
u_int64_t			time_now(void);
void				my_usleep(u_int64_t time);
int					check_var_dead(t_philo *philo);
void				display(t_philo *philo, char *s);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);
void				philo_eat(t_philo *philo);
void				clean_mutex(t_philo *philo);
void				destroy_failed_init_mutex(t_data *data, int until);
int					create_threads(t_data *data, t_philo *philo);
void				create_threads_error(t_data *data,
						t_philo *philo, int until);
void				*threads_monitor(void *philos);
void				join_threads(t_data *data, t_philo *philo);
int					check_if_any_dead(t_philo *philo);
int					check_if_a_philo_dead(t_philo *philo);
int					check_if_philos_feed(t_philo *philo);
void				free_allocated_memory(t_data *data, t_philo *philo);
int					init_mutex(t_data *data);
void				destroy_failed_init_mutex(t_data *data, int until);
void				init_philo(t_data *data, t_philo *philo);
void				*philo_routine(void *void_philo);
#endif
