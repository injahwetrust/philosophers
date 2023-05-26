/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:08:29 by bvaujour          #+#    #+#             */
/*   Updated: 2023/05/19 16:42:18 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	begin(t_data *data)
{
	int	i;

	i = -1;
	data->t0 = get_time(0);
	while (++i < data->rules.numphil)
		if (pthread_create(&data->p[i], NULL, &life, &data->philo[i]))
			return (1);
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
