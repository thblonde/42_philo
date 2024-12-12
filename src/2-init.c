/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblonde <thblonde@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:09:48 by thblonde          #+#    #+#             */
/*   Updated: 2024/12/12 14:10:02 by thblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* initialize forks */
static int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philos)
	{
		if (pthread_mutex_init(&data->philos[i].left_fork, NULL))
		{
			write(2, "Error: mutex initialization failed.\n", 36);
			while (i >= 0)
				pthread_mutex_destroy(&data->philos[i--].left_fork);
			return (1);
		}
		data->philos[i].id = i + 1;
	}
	return (0);
}

/* initialize mutex */
static int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->mutex_print, NULL))
		return (1);
	if (pthread_mutex_init(&data->mutex_dead, NULL))
		return (pthread_mutex_destroy(&data->mutex_print), 1);
	if (pthread_mutex_init(&data->mutex_full, NULL))
		return (pthread_mutex_destroy(&data->mutex_print),
			pthread_mutex_destroy(&data->mutex_dead), 1);
	if (pthread_mutex_init(&data->mutex_time, NULL))
		return (pthread_mutex_destroy(&data->mutex_print),
			pthread_mutex_destroy(&data->mutex_dead),
			pthread_mutex_destroy(&data->mutex_full), 1);
	return (0);
}

/* link forks and link philos to data */
static void	link_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philos - 1)
	{
		data->philos[i].right_fork = &data->philos[i + 1].left_fork;
	}
	data->philos[i].right_fork = &data->philos[0].left_fork;
	i = -1;
	while (++i < data->nbr_philos)
		data->philos[i].data = data;
}

/* fill struct with user input */
static void	input_init(int argc, char *argv[], t_data *data)
{
	data->nbr_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->start_time = get_time();
	if (argc == 6)
	{
		data->max_nbr_meals = ft_atol(argv[5]);
		data->five_args = true;
	}
}

int	init(int argc, char *argv[], t_data *data)
{
	input_init(argc, argv, data);
	data->philos = malloc(data->nbr_philos * sizeof(t_philo));
	if (!data->philos)
		return (write(2, "Error: memory allocation failed.\n", 32), 1);
	link_forks(data);
	if (init_forks(data))
		return (free(data->philos), 1);
	if (init_mutexes(data))
		return (free(data->philos), 1);
	return (0);
}
