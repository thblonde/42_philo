#include "philo.h"

void	take_left_fork(t_philo *philo)
{
        pthread_mutex_lock(&philo->m_left_fork);
        pthread_mutex_lock(&philo->data->m_printer);
        if (!philo->data->dead)    
            printf("%lu [%d] has taken a fork\n", get_time()
                - philo->data->start_t, philo->id);
        pthread_mutex_unlock(&philo->data->m_printer);
}

void	take_right_fork(t_philo *philo)
{
        pthread_mutex_lock(philo->m_right_fork);
        pthread_mutex_lock(&philo->data->m_printer);
        if (!philo->data->dead)
            printf("%lu [%d] has taken a fork\n", get_time()
                - philo->data->start_t, philo->id);
        pthread_mutex_unlock(&philo->data->m_printer);
}


void	eating(t_philo *philo)
{
    if (!philo->data->dead)
    {
		take_left_fork(philo);
		take_right_fork(philo);
	    pthread_mutex_lock(&philo->data->m_printer);
        if (!philo->data->dead)
		    printf("%lu [%d] is eating\n", get_time()
			    - philo->data->start_t, philo->id);
	    pthread_mutex_unlock(&philo->data->m_printer);
    	philo->last_meal_t = get_time();
	    philo->n_meals++;
        ft_usleep(philo->data->eat_t, philo);
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
		    printf("%lu [%d] is sleeping\n", get_time()
			    - philo->data->start_t, philo->id);
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
		    printf("%lu [%d] is thinking\n", get_time()
			    - philo->data->start_t, philo->id);
       	pthread_mutex_unlock(&philo->data->m_printer);
    }
}

