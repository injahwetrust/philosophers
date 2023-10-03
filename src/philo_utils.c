/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:57:48 by bvaujour          #+#    #+#             */
/*   Updated: 2023/05/31 11:25:57 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atol(const char *nptr)
{
	int		i;
	long	sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * nb);
}

long	get_time(long t0)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000 - t0);
}

void	ft_usleep(t_philo *philo, long time)
{
	long	begin;
	long	now;
	long	seq;

	seq = 0;
	while (seq <= 1 && seq >= 5000)
		seq = time / 2;
	begin = get_time(0);
	now = begin;
	while (!check(philo->data, philo) && (now - begin) < time)
	{
		usleep(seq);
		now = get_time(0);
	}
}

int	check(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->race);
	if (data->dead || !philo->num_of_eat)
	{
		pthread_mutex_unlock(&data->race);
		return (1);
	}
	pthread_mutex_unlock(&data->race);
	return (0);
}

void	print_meal(t_philo *philo)
{
	if (!check(philo->data, philo))
	{
		printf("%ld %d has taken a fork\n", philo->last_meal, philo->id);
		printf("%ld %d has taken a fork\n", philo->last_meal, philo->id);
		printf("%ld %d is eating\n", philo->last_meal, philo->id);
	}
}
