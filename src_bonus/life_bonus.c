/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:56:02 by injah             #+#    #+#             */
/*   Updated: 2023/05/25 17:44:20 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	release_sem(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numphil)
	{
		sem_post(data->sem);
		sem_post(data->meal);
		sem_post(data->bed);
		sem_post(data->book);
		i++;
	}
}
// void	satiated(t_data *data)
// {
	
// }

void	*dead(void *wallet)
{
	t_data	*data;
	long	lapse;

	data = (t_data *)wallet;
	while (1)
	{
		sem_wait(data->meal);
		lapse = time_lapse(data->last_meal);
		if (data->number_of_meal == 0)
		 	satiated(data);
		sem_post(data->meal);
		if (lapse > data->time_to_die)
		{
			sem_wait(data->sem);
			data->dead = 1;
			sem_post(data->sem);
			sem_wait(data->death_note);
			printf("%ld %d died\n", time_lapse(data->t0), data->id);
			release_sem(data);
			break ;
		}
		check(data);
	}
	return ((void *) 0);
}

void	eat(t_data *data)
{
	sem_wait(data->forks);
	sem_wait(data->forks);
	sem_wait(data->meal);
	data->eating = 1;
	data->last_meal = get_time();
	data->number_of_meal--;
	sem_post(data->meal);
	ft_usleep(data, data->time_to_eat);
	sem_post(data->forks);
	sem_post(data->forks);
}

void	life(t_data *data)
{
	pthread_create(&data->death, NULL, &dead, data);
	if (!(data->id % 2))
		ft_usleep(data, data->time_to_eat);
	if (data->numphil == 1)
	{
		ft_usleep(data, data->time_to_die);
		return ;
	}
	while (1)
	{
		sem_wait(data->sem);
		if (data->dead)
		{
			sem_post(data->sem);
			return ;
		}
		sem_post(data->sem);
		eat(data);
		sem_wait(data->bed);
		data->sleeping = 1;
		sem_post(data->bed);
		ft_usleep(data, data->time_to_sleep);
		sem_wait(data->book);
		data->thinking = 1;
		sem_post(data->book);
		ft_usleep(data, data->time_to_think);
	}
}
