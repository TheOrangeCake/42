/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_of_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:27:55 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/24 12:10:55 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*case_of_one_next(void *arg)
{
	t_parameter	*param;
	long		current;
	int			index;

	param = (t_parameter *)arg;
	index = 1;
	gettimeofday(&param->time, NULL);
	current = param->time.tv_usec / 1000 + param->time.tv_sec * 1000;
	printf("%10ld %5d is thinking\n", current - param->start_time, index);
	printf("%10ld %5d has taken a fork\n",
		current - param->start_time, index);
	usleep(param->time_die * 1000);
	printf("%10ld %5d died\n", current - param->start_time, index);
	return (NULL);
}

int	case_of_one(t_parameter *param)
{
	pthread_mutex_init(&param->p, NULL);
	param->philo = malloc(sizeof(pthread_t));
	if (param->philo == NULL)
		return (pthread_mutex_destroy(&param->p), 1);
	gettimeofday(&param->time, NULL);
	param->start_time = param->time.tv_usec
		/ 1000 + param->time.tv_sec * 1000;
	if (pthread_create(&param->philo[0], NULL,
			&case_of_one_next, param) != 0)
		return (free(param->philo), pthread_mutex_destroy(&param->p), 1);
	if (pthread_join(param->philo[0], NULL) != 0)
		return (free(param->philo), pthread_mutex_destroy(&param->p), 1);
	free(param->philo);
	pthread_mutex_destroy(&param->p);
	return (0);
}
