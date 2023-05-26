/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:51:05 by injah             #+#    #+#             */
/*   Updated: 2023/05/25 17:22:50 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	create_process(t_data *data)
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
			i++;
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

void	wait_process(t_data *data)
{
	int	i;

	i = 0;
	data->end_pid = wait(NULL);
	if (data->end_pid > 0)
	{
		printf("enfant n %d finished\n", data->end_pid);
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

int	check_arg(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (1);
	while (argc > 1)
	{
		i = 0;
		while (argv[argc - 1][i])
		{
			if (!(argv[argc - 1][i] >= '0' && argv[argc - 1][i] <= '9'))
				return (1);
			i++;
		}
		argc--;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_arg(ac, av))
		return (printf("Error args\n"));
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
