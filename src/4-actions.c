/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-actions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblonde <thblonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:21 by thblonde          #+#    #+#             */
/*   Updated: 2024/12/12 14:16:20 by thblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	if (!everybody_ate(philo->data))
		safe_print(philo, "has taken a fork");
}

void	take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (!everybody_ate(philo->data))
		safe_print(philo, "has taken a fork");
}

void	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		take_right_fork(philo);
		take_left_fork(philo);
	}
	else
	{
		take_left_fork(philo);
		take_right_fork(philo);
	}
	if (!everybody_ate(philo->data))
		safe_print(philo, "is eating");
	philo->nbr_meals++;
	actualize_meal_time(philo);
	ft_usleep(philo->data->time_to_eat);
	if (is_full(philo))
		increment_full(philo->data);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	if (!everybody_ate(philo->data))
		safe_print(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	if (!everybody_ate(philo->data))
		safe_print(philo, "is thinking");
}
