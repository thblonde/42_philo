/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6-print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblonde <thblonde@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:50 by thblonde          #+#    #+#             */
/*   Updated: 2024/12/12 14:11:17 by thblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* safely print philo state */
void	safe_print(t_philo *philo, const char *message)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	if (!is_dead(philo))
		printf("%lu %d %s\n", get_time() - philo->data->start_time, philo->id,
			message);
	pthread_mutex_unlock(&philo->data->mutex_print);
}

void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%lu %d is dead\n", get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->mutex_print);
}

void	print_all_eaten(t_data *data)
{
	pthread_mutex_lock(&data->mutex_print);
	printf("Every philosophers ate %d times\n", data->max_nbr_meals);
	pthread_mutex_unlock(&data->mutex_print);
}
