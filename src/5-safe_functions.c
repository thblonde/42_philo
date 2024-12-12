/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-safe_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblonde <thblonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:36 by thblonde          #+#    #+#             */
/*   Updated: 2024/12/12 15:17:11 by thblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* safely increment total number of full philos */
void	increment_full(t_data *data)
{
	pthread_mutex_lock(&data->mutex_full);
	data->full++;
	pthread_mutex_unlock(&data->mutex_full);
}

/* safely check if philo eat all his meals */
int	is_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_full);
	if (philo->nbr_meals == philo->data->max_nbr_meals)
	{
		pthread_mutex_unlock(&philo->data->mutex_full);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_full);
	return (0);
}

/* safely check if a philo died */
int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_dead);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_dead);
	return (0);
}

/* if number of full philo == number of philos => every philos ate enough */
int	everybody_ate(t_data *data)
{
	pthread_mutex_lock(&data->mutex_full);
	if (data->full == data->nbr_philos)
	{
		pthread_mutex_unlock(&data->mutex_full);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_full);
	return (0);
}
