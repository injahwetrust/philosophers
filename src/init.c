/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:49:26 by bvaujour          #+#    #+#             */
/*   Updated: 2023/05/19 16:19:31 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->race, NULL))
		return (1);
	if (pthread_mutex_init(&data->write, NULL))
		return (1);
	while (++i < data->rules.numphil)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
	return (0);
}

int	init_malloc(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->rules.numphil);
	if (!data->philo)
		return (2);
	data->p = malloc(sizeof(pthread_t) * data->rules.numphil);
	if (!data->p)
		return (2);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->rules.numphil);
	if (!data->forks)
		return (2);
	return (0);
}

int	init(t_data *data, char **argv)
{
	int		i;
	t_rules	rules;

	i = -1;
	rules.numphil = ft_atoi(argv[1]);
	rules.time_to_die = ft_atoi(argv[2]);
	rules.time_to_eat = ft_atoi(argv[3]);
	rules.time_to_sleep = ft_atoi(argv[4]);
	rules.time_to_think = (rules.time_to_die
			- rules.time_to_eat - rules.time_to_sleep) - 30;
	data->rules = rules;
	if (init_malloc(data) || init_mutex(data))
		return (1);
	while (++i < rules.numphil)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].last_meal = 0;
		data->philo[i].rules = rules;
		if (argv[5])
			data->philo[i].num_of_eat = ft_atoi(argv[5]);
		else
			data->philo[i].num_of_eat = -1;
	}
	return (0);
}
