/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:52:12 by bvaujour          #+#    #+#             */
/*   Updated: 2023/05/25 16:02:06 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# include <sys/time.h>
# include <errno.h>

struct	s_data;

typedef struct s_rules
{
	int				numphil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
}				t_rules;

typedef struct s_philo
{
	int				id;
	int				num_of_eat;
	long			last_meal;
	t_rules			rules;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	long long		t0;
	int				dead;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	pthread_t		*p;
	pthread_mutex_t	race;
	pthread_mutex_t	write;
	t_rules			rules;
}				t_data;

void	*life(void *valise);
long	get_time(long t0);
int		init(t_data *data, char **argv);
void	dead(t_data *data);
int		ft_atoi(const char *nptr);
void	printf_meal(t_philo *philo);
void	ft_usleep(t_data *data, long time);
void	print_meal(t_philo *philo);
int		check(t_data *data, t_philo *philo);

#endif