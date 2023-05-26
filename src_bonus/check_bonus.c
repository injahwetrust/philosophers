/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:23:17 by bvaujour          #+#    #+#             */
/*   Updated: 2023/05/25 17:06:20 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	check2(t_data *data)
{
	sem_wait(data->book);
	if (data->thinking == 1)
	{
		sem_wait(data->death_note);
		printf("%ld %d is thinking\n", time_lapse(data->t0), data->id);
		sem_post(data->death_note);
		data->thinking = 0;
	}
	sem_post(data->book);
}

void	check(t_data *data)
{
	sem_wait(data->meal);
	if (data->eating == 1)
	{
		sem_wait(data->death_note);
		printf("%ld %d has taken a fork\n", time_lapse(data->t0), data->id);
		printf("%ld %d has taken a fork\n", time_lapse(data->t0), data->id);
		printf("%ld %d is eating\n", time_lapse(data->t0), data->id);
		sem_post(data->death_note);
		data->eating = 0;
	}
	sem_post(data->meal);
	sem_wait(data->bed);
	if (data->sleeping == 1)
	{
		sem_wait(data->death_note);
		printf("%ld %d is sleeping\n", time_lapse(data->t0), data->id);
		sem_post(data->death_note);
		data->sleeping = 0;
	}
	sem_post(data->bed);
	check2(data);
}
