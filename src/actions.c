/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblonde <thblonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:41:54 by thblonde          #+#    #+#             */
/*   Updated: 2024/11/09 19:09:24 by thblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_left_fork(t_philo *philo)
{
	(void)philo;
	return ;

}

// void	take_right_fork(t_philo *philo)
// {
//void	take_forks(t_philo *philo)

// }

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->m_right_fork);
		pthread_mutex_lock(&philo->data->m_printer);
		if (!philo->data->dead)
			printf("%lu [%d] has taken a fork\n", get_time()
				- philo->data->start_t, philo->id);
		pthread_mutex_unlock(&philo->data->m_printer);
		pthread_mutex_lock(&philo->m_left_fork);
		pthread_mutex_lock(&philo->data->m_printer);
		if (!philo->data->dead)
			printf("%lu [%d] has taken a fork\n", get_time()
				- philo->data->start_t, philo->id);
		pthread_mutex_unlock(&philo->data->m_printer);
	}
	else
	{
		pthread_mutex_lock(&philo->m_left_fork);
		pthread_mutex_lock(&philo->data->m_printer);
		if (!philo->data->dead)
			printf("%lu [%d] has taken a fork\n", get_time()
				- philo->data->start_t, philo->id);
		pthread_mutex_unlock(&philo->data->m_printer);
		pthread_mutex_lock(philo->m_right_fork);
		pthread_mutex_lock(&philo->data->m_printer);
		if (!philo->data->dead)
			printf("%lu [%d] has taken a fork\n", get_time()
				- philo->data->start_t, philo->id);
		pthread_mutex_unlock(&philo->data->m_printer);
	}
}

void	eating(t_philo *philo)
{
	if (!philo->data->dead)
	{
		// take_left_fork(philo);
		// take_right_fork(philo);
		take_forks(philo);
		pthread_mutex_lock(&philo->data->m_printer);
		if (!philo->data->dead)
			printf("%lu [%d] is eating\n", get_time() - philo->data->start_t,
				philo->id);
		pthread_mutex_unlock(&philo->data->m_printer);
		philo->last_meal_t = get_time();
		philo->n_meals++;
		ft_usleep(philo->data->eat_t, philo);
		philo->last_meal_t = get_time();
		pthread_mutex_unlock(&philo->m_left_fork);
		pthread_mutex_unlock(philo->m_right_fork);
	}
}

void	sleeping(t_philo *philo)
{
	if (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->data->m_printer);
		if (!philo->data->dead)
			printf("%lu [%d] is sleeping\n", get_time() - philo->data->start_t,
				philo->id);
		pthread_mutex_unlock(&philo->data->m_printer);
		ft_usleep(philo->data->sleep_t, philo);
	}
}

void	thinking(t_philo *philo)
{
	if (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->data->m_printer);
		if (!philo->data->dead)
			printf("%lu [%d] is thinking\n", get_time() - philo->data->start_t,
				philo->id);
		pthread_mutex_unlock(&philo->data->m_printer);
	}
}
