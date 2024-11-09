/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblonde <thblonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:42:09 by thblonde          #+#    #+#             */
/*   Updated: 2024/11/09 19:10:21 by thblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					n_philos;
	long				die_t;
	long				eat_t;
	long				sleep_t;
	int					max_meals;
	bool				five_args;
	_Atomic bool dead;
	_Atomic int full;
	long				start_t;
	pthread_mutex_t		m_printer;
	pthread_t			monitor;
	t_philo				*philos;
}						t_data;

typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		m_left_fork;
	pthread_mutex_t		*m_right_fork;
	int					id;
	int					n_meals;
	_Atomic long last_meal_t;
	t_data				*data;
}						t_philo;

int						init(int argc, char *argv[], t_data *data);
int						threads(t_data *data);
void					take_left_fork(t_philo *philo);
void					take_right_fork(t_philo *philo);
void					eating(t_philo *philo);
void					sleeping(t_philo *philo);
void					thinking(t_philo *philo);
void					print_dead(t_philo *philo);
void					print_all_eaten(t_data *data);
void					*is_alone(void *alone);
int						case_one(t_data *data);
void					take_forks(t_philo *philo);

int						ft_isspace(int c);
int						ft_isdigit(int c);
long					ft_atol(const char *str);
long int				get_time(void);
void					ft_usleep(long int time_in_ms, t_philo *philo);

#endif
