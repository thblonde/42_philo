/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblonde <thblonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:11:44 by thblonde          #+#    #+#             */
/*   Updated: 2024/12/12 15:14:03 by thblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					nbr_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					max_nbr_meals;
	bool				five_args;
	pthread_mutex_t		mutex_dead;
	bool				dead;
	pthread_mutex_t		mutex_full;
	int					full;
	long				start_time;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		mutex_time;
	pthread_t			monitor;
	t_philo				*philos;
}						t_data;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		*right_fork;
	int					nbr_meals;
	long				time_last_meal;
	t_data				*data;
}						t_philo;

/* init struct */
int						init(int argc, char *argv[], t_data *data);

/* create and join threads */
int						threads(t_data *data);

/* routine actions */
void					eating(t_philo *philo);
void					take_left_fork(t_philo *philo);
void					take_right_fork(t_philo *philo);
void					sleeping(t_philo *philo);
void					thinking(t_philo *philo);

/* print functions */
void					safe_print(t_philo *philo, const char *message);
void					print_dead(t_philo *philo);
void					print_all_eaten(t_data *data);

/* in case of only one philo */
void					*is_alone(void *alone);
int						case_one(t_data *data);

/* time functions */
long int				get_time(void);
void					ft_usleep(long time_in_ms);
void					actualize_meal_time(t_philo *philo);
int						check_time(t_philo *philo);

/* safe functions */
int						is_dead(t_philo *philo);
int						is_full(t_philo *philo);
void					increment_full(t_data *data);
int						everybody_ate(t_data *data);

/* utils */
int						ft_isspace(int c);
int						ft_isdigit(int c);
long					ft_atol(const char *str);

#endif