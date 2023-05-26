/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:51:28 by injah             #+#    #+#             */
/*   Updated: 2023/05/25 16:14:40 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/types.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	long		t0;
	long		last_meal;
	int			numphil;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			time_to_think;
	int			number_of_meal;
	int			id;
	sem_t		*sem;
	sem_t		*bed;
	sem_t		*book;
	sem_t		*death_note;
	sem_t		*forks;
	sem_t		*meal;
	pid_t		*pids;
	pid_t		end_pid;
	pthread_t	death;
	int			dead;
	int			eating;
	int			sleeping;
	int			thinking;
}t_data;

int		init_data(t_data *data, int ac, char **av);
void	end(t_data *data);
void	life(t_data *data);
long	get_time(void);
long	time_lapse(long t0);
void	ft_usleep(t_data *data, long time);
void	check(t_data *data);

#endif