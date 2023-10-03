/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:23:17 by bvaujour          #+#    #+#             */
/*   Updated: 2023/05/31 11:31:03 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	check2(t_data *data)
{
	sem_wait(data->book);
	if (data->thinking == 1)
	{
		sem_wait(data->death_note);
		printf("%ld %d %sis thinking%s\n", time_lapse(data->t0),
			data->id, BLUE, WHITE);
		sem_post(data->death_note);
		data->thinking = 0;
	}
	sem_post(data->book);
	sem_wait(data->meal);
	if (data->eating == 1)
	{
		data->eating = 0;
		data->number_of_meal--;
		sem_wait(data->death_note);
		printf("%ld %d has taken a fork\n", time_lapse(data->t0),
			data->id);
		printf("%ld %d has taken a fork\n", time_lapse(data->t0),
			data->id);
		printf("%ld %d %sis eating%s\n", time_lapse(data->t0),
			data->id, GREEN, WHITE);
		sem_post(data->death_note);
	}
	sem_post(data->meal);
}

void	check(t_data *data)
{
	sem_wait(data->bed);
	if (data->sleeping == 1)
	{
		sem_wait(data->death_note);
		printf("%ld %d %sis sleeping%s\n", time_lapse(data->t0),
			data->id, YELLOW, WHITE);
		sem_post(data->death_note);
		data->sleeping = 0;
	}
	sem_post(data->bed);
	check2(data);
}
