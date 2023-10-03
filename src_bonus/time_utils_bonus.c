/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:22:24 by injah             #+#    #+#             */
/*   Updated: 2023/05/31 11:43:31 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	time_lapse(long t0)
{
	return (get_time() - t0);
}

void	ft_usleep(t_data *data, long time)
{
	long	now;
	long	seq;

	seq = 0;
	while (seq <= 1 && seq >= 5000)
		seq = time / 2;
	now = get_time();
	while (time_lapse(now) < time)
	{
		sem_wait(data->sem);
		if (data->dead)
		{
			sem_post(data->sem);
			return ;
		}
		sem_post(data->sem);
		usleep(seq);
	}
}

int	table(t_data *data)
{
	if ((data->number_of_meal == 0 && data->id == data->numphil))
	{
		sem_wait(data->sem);
		data->dead = 1;
		sem_post(data->sem);
		release_sem(data);
		return (1);
	}
	return (0);
}

int	taggle(t_data *data, long lapse)
{
	if (lapse > data->time_to_die)
	{
		sem_wait(data->sem);
		data->dead = 1;
		sem_post(data->sem);
		sem_wait(data->death_note);
		printf("%ld %d %sdied%s\n", time_lapse(data->t0),
			data->id, RED, WHITE);
		release_sem(data);
		return (1);
	}
	return (0);
}
