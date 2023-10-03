/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:50:43 by injah             #+#    #+#             */
/*   Updated: 2023/05/31 12:46:29 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

long	ft_atol(const char *nptr)
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

static void	init_sem(t_data *data)
{
	sem_unlink("/sema7");
	sem_unlink("/forks");
	sem_unlink("/death");
	sem_unlink("/meal");
	sem_unlink("/bed");
	sem_unlink("/book");
	data->bed = sem_open("/bed", O_CREAT, 0644, 1);
	data->book = sem_open("/book", O_CREAT, 0644, 1);
	data->sem = sem_open("/sema7", O_CREAT, 0644, 1);
	data->death_note = sem_open("/death", O_CREAT, 0644, 1);
	data->meal = sem_open("/meal", O_CREAT, 0644, 1);
	data->forks = sem_open("/forks", O_CREAT, 0644, data->numphil);
}

static void	init_flat(t_data *data)
{
	data->time_to_think = data->time_to_die - data->time_to_eat
		- data->time_to_sleep - 40;
	if (data->time_to_think < 0)
		data->time_to_think = 0;
	data->eating = 0;
	data->sleeping = 0;
	data->dead = 0;
	data->thinking = 0;
}

int	init_data(t_data *data, int ac, char **av)
{
	data->numphil = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (ac == 6 && ft_atol(av[5]) > 0)
		data->number_of_meal = ft_atol(av[5]);
	else
		data->number_of_meal = -1;
	data->pids = malloc(sizeof(pid_t) * data->numphil);
	if (!data->pids)
		return (1);
	init_flat(data);
	init_sem(data);
	if (data->sem == SEM_FAILED || data->forks == SEM_FAILED
		||data->death_note == SEM_FAILED || data->meal == SEM_FAILED
		|| data->book == SEM_FAILED || data->bed == SEM_FAILED)
		return (free(data->pids), 1);
	data->t0 = get_time();
	data->last_meal = data->t0;
	return (0);
}

void	end(t_data *data)
{
	pthread_join(data->death, NULL);
	free(data->pids);
	sem_unlink("/sema7");
	sem_close(data->sem);
	sem_unlink("/forks");
	sem_close(data->forks);
	sem_unlink("/death");
	sem_close(data->death_note);
	sem_unlink("/meal");
	sem_close(data->meal);
	sem_unlink("/bed");
	sem_close(data->bed);
	sem_unlink("/book");
	sem_close(data->book);
	exit (0);
}
