/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblonde <thblonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:42:00 by thblonde          #+#    #+#             */
/*   Updated: 2024/11/09 18:42:01 by thblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Check arguments validity
static int	errors_parsing(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]) || ft_atol(argv[i]) < 1
				|| ft_atol(argv[i]) > INT_MAX)
				return (1);
		}
	}
	if (ft_atol(argv[1]) > 200 || ft_atol(argv[2]) <= 60
		|| ft_atol(argv[3]) <= 60 || ft_atol(argv[4]) <= 60)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc < 5 || argc > 6 || errors_parsing(argc, argv))
		return (write(2, "Error: Invalid arguments.\n", 26), 1);
	if (init(argc, argv, &data))
		return (1);
	if (threads(&data))
		return (free(data.philos), 1);
	free(data.philos);
	return (0);
}
