#include "philo.h"

/* Initialize forks */
static int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_mutex_init(&data->philos[i].m_left_fork, NULL))
		{
			write(2, "Error: mutex initialization failed.\n", 36);
			while (i >= 0)
				pthread_mutex_destroy(&data->philos[i--].m_left_fork);
			return (1);
		}
		data->philos[i].id = i + 1;
	}
	return (0);
}

/* Initialize printer counters and starting */
static int	init_mutexes(t_data *data)
{
    pthread_mutex_init(&data->m_printer, NULL);
	return (0);
}

// Link forks and link philos to data
static void	link_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos - 1)
	{
		data->philos[i].m_right_fork = &data->philos[i + 1].m_left_fork;
	}
	data->philos[i].m_right_fork = &data->philos[0].m_left_fork;
	i = -1;
	while (++i < data->n_philos)
		data->philos[i].data = data;
}

// Fill struct with input
static void	input_init(int argc, char *argv[], t_data *data)
{
	data->n_philos = ft_atol(argv[1]);
	data->die_t = ft_atol(argv[2]);
	data->eat_t = ft_atol(argv[3]);
	data->sleep_t = ft_atol(argv[4]);
	data->start_t = get_time();
	if (argc == 6)
	{
		data->max_meals = ft_atol(argv[5]);
		data->five_args = true;
	}
}

int	init(int argc, char *argv[], t_data *data)
{
    input_init(argc, argv, data);
	data->philos = malloc(data->n_philos * sizeof(t_philo));
	if (!data->philos)
		return (write(2, "Error: memory allocation failed.\n", 32), 1);
	link_forks(data);
	if (init_forks(data))
		return (free(data->philos), 1);
	if (init_mutexes(data))
		return (free(data->philos), 1);
	return (0);
}
