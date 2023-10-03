/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:02:14 by bvaujour          #+#    #+#             */
/*   Updated: 2023/05/31 11:27:12 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	odd(t_philo *philo)
{
	if (!pthread_mutex_lock(&philo->data->forks[philo->id - 1])
		&& !pthread_mutex_lock(&philo->data->forks[philo->id
				% philo->rules.numphil]))
	{
		pthread_mutex_lock(&philo->data->race);
		philo->last_meal = get_time(philo->data->t0);
		pthread_mutex_unlock(&philo->data->race);
		pthread_mutex_lock(&philo->data->write);
		print_meal(philo);
		pthread_mutex_unlock(&philo->data->write);
		ft_usleep(philo, philo->rules.time_to_eat);
		pthread_mutex_lock(&philo->data->race);
		philo->num_of_eat--;
		pthread_mutex_unlock(&philo->data->race);
	}
	if (!pthread_mutex_unlock(&philo->data->forks[philo->id
				% philo->rules.numphil]) && !pthread_mutex_unlock
		(&philo->data->forks[philo->id - 1]))
		return ;
}

void	eat(t_philo *philo)
{
	if (philo->rules.numphil == 1)
		return ;
	if (philo->id % 2)
	{
		if (!pthread_mutex_lock(&philo->data->forks[philo->id
					% philo->rules.numphil]) && !pthread_mutex_lock
			(&philo->data->forks[philo->id - 1]))
		{
			pthread_mutex_lock(&philo->data->race);
			philo->last_meal = get_time(philo->data->t0);
			pthread_mutex_unlock(&philo->data->race);
			pthread_mutex_lock(&philo->data->write);
			print_meal(philo);
			pthread_mutex_unlock(&philo->data->write);
			ft_usleep(philo, philo->rules.time_to_eat);
			pthread_mutex_lock(&philo->data->race);
			philo->num_of_eat--;
			pthread_mutex_unlock(&philo->data->race);
		}
		if (!pthread_mutex_unlock(&philo->data->forks[philo->id - 1])
			&& !pthread_mutex_unlock(&philo->data->forks
				[philo->id % philo->rules.numphil]))
			return ;
	}
	odd(philo);
}

void	*life(void *valise)
{
	t_philo	*philo;

	philo = (t_philo *) valise;
	if (philo->id % 2 && philo->rules.numphil > 1)
		usleep(philo->rules.time_to_eat);
	while (1)
	{
		eat(philo);
		pthread_mutex_lock(&philo->data->write);
		if (!check(philo->data, philo) && philo->rules.numphil > 1)
			printf("%ld %d is sleeping\n", get_time(philo->data->t0), philo->id);
		pthread_mutex_unlock(&philo->data->write);
		ft_usleep(philo, philo->rules.time_to_sleep);
		pthread_mutex_lock(&philo->data->write);
		if (!check(philo->data, philo) && philo->rules.numphil > 1)
			printf("%ld %d is thinking\n", get_time(philo->data->t0), philo->id);
		pthread_mutex_unlock(&philo->data->write);
		ft_usleep(philo, philo->rules.time_to_think);
		if (check(philo->data, philo))
			return ((void *) 0);
	}
}

void	dead_note(t_data *data, int i)
{
	pthread_mutex_lock(&data->race);
	data->dead = 1;
	pthread_mutex_unlock(&data->race);
	pthread_mutex_lock(&data->write);
	printf("%ld %d died\n", get_time(data->t0), i);
	pthread_mutex_unlock(&data->write);
}

void	dead(t_data *data)
{
	int	i;
	int	life;
	int	check_rest;

	i = 0;
	check_rest = 0;
	while (1)
	{
		pthread_mutex_lock(&data->race);
		check_rest += data->philo[i].num_of_eat;
		life = get_time(data->t0) - data->philo[i].last_meal;
		pthread_mutex_unlock(&data->race);
		if (life > data->rules.time_to_die && data->philo[i].num_of_eat)
		{
			dead_note(data, i + 1);
			return ;
		}
		if (i == data->rules.numphil - 1 && !check_rest)
			return ;
		else if (i == data->rules.numphil - 1 && check_rest)
			check_rest = 0;
		i++;
		i = i % data->rules.numphil;
	}
}
