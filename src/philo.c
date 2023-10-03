/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:08:29 by bvaujour          #+#    #+#             */
/*   Updated: 2023/05/31 12:07:17 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	begin(t_data *data)
{
	int	i;

	i = -1;
	data->t0 = get_time(0);
	while (++i < data->rules.numphil)
	{
		if (pthread_create(&data->p[i], NULL, &life, &data->philo[i]))
		{
			while (i <= 0)
			{
				pthread_join(data->p[i], NULL);
				i--;
			}
			return (1);
		}
	}
	dead(data);
	i = -1;
	while (++i < data->rules.numphil)
		if (pthread_join(data->p[i], NULL))
			return (2);
	return (0);
}

int	end(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->rules.numphil)
		if (pthread_mutex_destroy(&data->forks[i]))
			return (1);
	if (pthread_mutex_destroy(&data->race))
		return (1);
	if (pthread_mutex_destroy(&data->write))
		return (1);
	free(data->forks);
	free(data->p);
	free(data->philo);
	return (0);
}

int	check_arg(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (1);
	if (ft_atol(argv[1]) <= 0 || ft_atol(argv[1]) >= 200)
		return (1);
	if (ft_atol(argv[2]) > IMAX || ft_atol(argv[3]) > IMAX
		|| ft_atol(argv[4]) > IMAX)
		return (1);
	if (ft_atol(argv[2]) < 60 || ft_atol(argv[3]) < 60
		|| ft_atol(argv[4]) < 60)
		return (1);
	while (argc > 1)
	{
		i = 0;
		while (argv[argc - 1][i])
		{
			if (!(argv[argc - 1][i] >= '0' && argv[argc - 1][i] <= '9'))
				return (1);
			i++;
		}
		argc--;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		error;

	data.dead = 0;
	if (check_arg(argc, argv))
		return (printf("Problem with args\n"));
	if (argv[5] && ft_atol(argv[5]) == 0)
		return (0);
	error = 0;
	error = init(&data, argv);
	if (error)
		return (printf("Problem with allocations\n"));
	error = begin(&data);
	if (error == 1)
		return (printf("Problem creating threads\n"));
	if (error == 2)
		return (printf("Problem joining threads\n"));
	error = end(&data);
	if (error)
		return (printf("problem closing mutex\n"));
	return (0);
}
