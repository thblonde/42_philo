/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblonde <thblonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:41:56 by thblonde          #+#    #+#             */
/*   Updated: 2024/11/09 18:41:57 by thblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_printer);
	printf("%lu [%d] is dead\n", get_time() - philo->data->start_t, philo->id);
	pthread_mutex_unlock(&philo->data->m_printer);
}

void	print_all_eaten(t_data *data)
{
	pthread_mutex_lock(&data->m_printer);
	printf("Every philosophers ate %d times\n", data->max_meals);
	pthread_mutex_unlock(&data->m_printer);
}

void	*is_alone(void *alone)
{
	t_philo	*philo;

	philo = (t_philo *)alone;
	take_left_fork(philo);
	ft_usleep(philo->data->die_t, philo);
	pthread_mutex_lock(&philo->data->m_printer);
	printf("%lu [%d] is dead\n", get_time() - philo->data->start_t, philo->id);
	pthread_mutex_unlock(&philo->data->m_printer);
	philo->data->dead = true;
	return (NULL);
}

int	case_one(t_data *data)
{
	if (pthread_create(&data->philos[0].thread, NULL, &is_alone,
			&data->philos[0]))
		return (1);
	if (pthread_join(data->philos[0].thread, NULL))
		return (1);
	return (0);
}
