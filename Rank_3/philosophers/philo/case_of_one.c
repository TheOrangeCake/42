/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_of_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:27:55 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/18 15:45:36 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*case_of_one_next(void *arg)
{
	t_parameter	*param;

	param = (t_parameter *)arg;
	print_message(param, 1, THINK);
	print_message(param, 1, F_FORK);
	usleep(param->time_die * 1000);
	print_message(param, 1, DIE);
	return (NULL);
}

int	case_of_one(t_parameter *param)
{
	param->p = ft_calloc(1, sizeof(pthread_mutex_t));
	if (param->p == NULL)
		return (1);
	param->philo = malloc(sizeof(pthread_t));
	if (param->philo == NULL)
		return (free(param->p), 1);
	gettimeofday(&param->time, NULL);
	param->start_time = param->time.tv_usec
		/ 1000 + param->time.tv_sec * 1000;
	if (pthread_create(&param->philo[0], NULL,
			&case_of_one_next, param) != 0)
		return (free(param->philo), 1);
	if (pthread_join(param->philo[0], NULL) != 0)
		return (free(param->philo), 1);
	free(param->philo);
	free(param->p);
	return (0);
}
