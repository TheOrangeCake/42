/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_of_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:27:55 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/17 22:22:23 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*case_of_one_next(void *arg)
{
	t_parameter	*params;

	params = (t_parameter *)arg;
	print_message(params, 1, THINK);
	print_message(params, 1, F_FORK);
	usleep(params->time_die * 1000);
	print_message(params, 1, DIE);
	return (NULL);
}

int	case_of_one(t_parameter *params)
{
	params->philo->single = malloc(sizeof(pthread_t));
	if (params->philo->single == NULL)
		return (1);
	gettimeofday(&params->philo->time, NULL);
	params->start_time = params->philo->time.tv_usec
		/ 1000 + params->philo->time.tv_sec * 1000;
	if (pthread_create(&params->philo->single[0], NULL,
			&case_of_one_next, params) != 0)
		return (free(params->philo->single), 1);
	if (pthread_join(params->philo->single[0], NULL) != 0)
		return (free(params->philo->single), 1);
	free(params->philo->single);
	return (0);
}
