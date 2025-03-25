/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:34:35 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/25 09:50:50 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define THINK 1
# define FORK 2
# define EAT 3
# define SLEEP 4

typedef struct s_parameter
{
	int				numb;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			must_eat;
	struct timeval	time;
	long			start_time;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*t;
	pthread_mutex_t	p;
	pthread_mutex_t	dead;
	pthread_t		*philo;
	pthread_t		monitor;
	long			*timetable;
	int				die;
	int				monitor_flag;
}	t_parameter;

typedef struct s_index
{
	t_parameter	*param;
	int			index;
}	t_index;

typedef struct s_monitor
{
	int				i;
	long			current;
	int				count;
	struct timeval	time;
	int				flag;
}	t_monitor;

typedef struct s_local
{
	int				index;
	int				flag;
	int				eaten;
	int				finish;
	struct timeval	time;
	long			last_eat;
	int				left_fork;
}	t_local;

long	ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
int		input_check(char **av);
void	free_all(t_parameter *params);
int		init_parameters(t_parameter *params, char **av, int ac);
void	init_local(t_parameter *params, t_local *local, int index);
int		init_rest(t_parameter *params);
void	print_message(t_parameter *params, int index, int code);

void	*routine(void *arg);
int		case_of_one(t_parameter *params);

#endif