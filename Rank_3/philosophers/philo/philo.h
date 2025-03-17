/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:34:35 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/17 15:56:53 by hoannguy         ###   ########.fr       */
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
	pthread_mutex_t	*mutex;
	pthread_t		*single;
	int				*fork;
	struct timeval	t;
	int				index;
	int				i;
	int				j;
}	t_philo;

typedef struct s_wrapper
{
	t_philo	*philo;
	int		index;
}	t_wrapper;

long	ft_atoi(char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

int	case_of_one(t_philo philo);

#endif