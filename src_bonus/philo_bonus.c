/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:51:05 by injah             #+#    #+#             */
/*   Updated: 2023/06/12 15:24:59 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static int	create_process(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numphil)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			return (1);
		if (data->pids[i] == 0)
		{
			data->id = i + 1;
			life(data);
			end(data);
		}
		else
		{
			usleep(500);
			i++;
		}
	}
	return (0);
}

void	end2(t_data *data)
{
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

static void	wait_process(t_data *data)
{
	int	i;
	int	status;

	status = -1;
	i = 0;
	data->end_pid = wait(&status);
	if (data->end_pid > 0)
	{
		while (i < data->numphil)
		{
			if (data->end_pid != data->pids[i])
				if (kill(data->pids[i], SIGKILL) == -1)
					printf ("failed to kill processes\n");
			i++;
		}
	}
	end2(data);
}

static int	check_arg(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (1);
	if (ft_atol(argv[1]) <= 0 || ft_atol(argv[1]) > 200)
		return (1);
	if (ft_atol(argv[2]) > IMAX || ft_atol(argv[3]) > IMAX
		|| ft_atol(argv[4]) > IMAX)
		return (1);
	if (ft_atol(argv[2]) < 60 || ft_atol(argv[3]) < 60
		|| ft_atol(argv[4]) < 60)
		return (1);
	if (argv[5] && (ft_atol(argv[5]) < 0 || ft_atol(argv[5]) > IMAX))
		return (1);
	while (argc > 1)
	{
		i = -1;
		while (argv[argc - 1][++i])
			if (!(argv[argc - 1][i] >= '0' && argv[argc - 1][i] <= '9'))
				return (1);
		if (i >= 12)
			return (1);
		argc--;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_arg(ac, av))
		return (printf("Error args\n"));
	if (av[5] && ft_atol(av[5]) == 0)
		return (0);
	if (init_data(&data, ac, av))
		return (printf("Error init\n"));
	if (create_process(&data))
	{
		printf("Error creating process\n");
		end(&data);
	}
	wait_process(&data);
	return (0);
}
