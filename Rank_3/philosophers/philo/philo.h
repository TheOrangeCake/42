/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:34:35 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/15 10:21:49 by hoannguy         ###   ########.fr       */
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

typedef struct s_philo
{
	int				numb;
	long			die;
	long			eat;
	long			sleep;
	long			must_eat;
	pthread_mutex_t	mutex;
	int				i;
	int				j;
	int				*fork;
	struct timeval	t;
}	t_philo;

typedef struct s_time
{
	int	hour;
	int	minute;
	int	second;
}	t_time;

long	ft_atoi(char *nptr);
void	showtime(void);

int	case_of_one(t_philo philo);

#endif