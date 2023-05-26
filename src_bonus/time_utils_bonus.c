/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:22:24 by injah             #+#    #+#             */
/*   Updated: 2023/05/25 17:17:16 by bvaujour         ###   ########.fr       */
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
		usleep(100);
	}
}
