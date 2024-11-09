/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblonde <thblonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:42:02 by thblonde          #+#    #+#             */
/*   Updated: 2024/11/09 19:13:38 by thblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Routine executed by the monitor
void	*monitor(void *p_data)
{
	t_data	*data;
	int		i;

	data = (t_data *)p_data;
	while (1)
	{
		i = 0;
		while (i < data->n_philos)
		{
			if (get_time() - data->philos[i].last_meal_t > data->die_t)
			{
				data->dead = true;
				print_dead(&data->philos[i]);
				return (NULL);
			}
			if (data->five_args && data->full == data->n_philos)
				return (print_all_eaten(data), NULL);
			i++;
		}
	}
	return (NULL);
}

// Routine executed by every philos
void	*routine(void *p_philo)
{
	t_philo	*philo;

	philo = (t_philo *)p_philo;
	while (!philo->data->dead)
	{
		if (philo->data->five_args && philo->n_meals == philo->data->max_meals)
		{
			philo->data->full++;
			return (NULL);
		}
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	threads(t_data *data)
{
	int	i;

	i = -1;
	if (data->n_philos == 1)
	{
		if (case_one(data))
			return (1);
		return (0);
	}
	while (++i < data->n_philos)
	{
		data->philos[i].last_meal_t = get_time();
		if (pthread_create(&data->philos[i].thread, NULL, &routine,
				&data->philos[i]))
			return (1);
	}
	if (pthread_create(&data->monitor, NULL, &monitor, data))
		return (1);
	i = -1;
	while (++i < data->n_philos)
		if (pthread_join(data->philos[i].thread, NULL))
			return (1);
	if (pthread_join(data->monitor, NULL))
		return (1);
	return (0);
}
