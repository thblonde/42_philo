/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblonde <thblonde@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:06:30 by thblonde          #+#    #+#             */
/*   Updated: 2024/12/12 14:09:39 by thblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9') || c == '+' || c == '-')
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	long int	nb;
	int			sign;

	nb = 0;
	sign = 1;
	while (ft_isspace((int)*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = (-1);
		str++;
	}
	while (ft_isdigit((int)*str))
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (sign * nb);
}

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
