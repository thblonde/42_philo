/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-threads.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblonde <thblonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:06 by thblonde          #+#    #+#             */
/*   Updated: 2024/12/18 09:35:41 by thblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* monitor thread */
void	*check_dead(void *p_data)
{
	t_data	*data;
	int		i;

	data = (t_data *)p_data;
	while (1)
	{
		i = -1;
		while (++i < data->nbr_philos)
		{
			if (check_time(&data->philos[i]))
			{
				pthread_mutex_lock(&data->mutex_dead);
				data->dead = true;
				pthread_mutex_unlock(&data->mutex_dead);
				print_dead(&data->philos[i]);
				return (NULL);
			}
			if (data->five_args && everybody_ate(data))
			{
				print_all_eaten(data);
				return (NULL);
			}
		}
	}
	return (NULL);
}

/* philo routine */
void	*routine(void *p_philo)
{
	t_philo	*philo;

	philo = (t_philo *)p_philo;
	while (!is_dead(philo) && !everybody_ate(philo->data))
	{
		eating(philo);
		thinking(philo);
		sleeping(philo);
	}
	return (NULL);
}

void	*is_alone(void *alone)
{
	t_philo	*philo;

	philo = (t_philo *)alone;
	take_left_fork(philo);
	ft_usleep(philo->data->time_to_die);
	safe_print(philo, "is dead");
	pthread_mutex_unlock(&philo->left_fork);
	return (NULL);
}

/* if only one philo */
int	case_one(t_data *data)
{
	if (pthread_create(&data->philos[0].thread, NULL, &is_alone,
			&data->philos[0]))
		return (1);
	if (pthread_join(data->philos[0].thread, NULL))
		return (1);
	return (0);
}

/* create and join threads */
int	threads(t_data *data)
{
	int	i;

	i = -1;
	if (data->nbr_philos == 1)
	{
		if (case_one(data))
			return (1);
		return (0);
	}
	while (++i < data->nbr_philos)
	{
		data->philos[i].time_last_meal = get_time();
		if (pthread_create(&data->philos[i].thread, NULL, &routine,
				&data->philos[i]))
			return (1);
	}
	if (pthread_create(&data->monitor, NULL, &check_dead, data))
		return (1);
	i = -1;
	while (++i < data->nbr_philos)
		if (pthread_join(data->philos[i].thread, NULL))
			return (1);
	if (pthread_join(data->monitor, NULL))
		return (1);
	return (0);
}
