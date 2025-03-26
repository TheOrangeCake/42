/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:27:14 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/26 13:01:12 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	takefork(t_parameter *param, t_local *local)
{
	pthread_mutex_lock(&param->mutex[local->index]);
	print_message(param, local->index + 1, FORK);
	pthread_mutex_lock(&param->mutex[local->left_fork]);
	print_message(param, local->index + 1, FORK);
	print_message(param, local->index + 1, EAT);
	gettimeofday(&local->time, NULL);
	local->last_eat = local->time.tv_usec / 1000 + local->time.tv_sec * 1000;
	pthread_mutex_lock(&param->t[local->index]);
	param->timetable[local->index] = local->last_eat + param->time_die;
	pthread_mutex_unlock(&param->t[local->index]);
	usleep(param->time_eat * 1000);
	local->eaten++;
	local->flag = 1;
	pthread_mutex_unlock(&param->mutex[local->index]);
	pthread_mutex_unlock(&param->mutex[local->left_fork]);
	if (local->eaten == param->must_eat)
	{
		local->finish = 1;
		pthread_mutex_lock(&param->t[local->index]);
		param->timetable[local->index] = -1;
		pthread_mutex_unlock(&param->t[local->index]);
	}
}

void	routine_helper(t_parameter *param, t_local *local)
{
	print_message(param, local->index + 1, THINK);
	if (local->index % 2 == 0)
		takefork(param, local);
	else
	{
		usleep(1000);
		takefork(param, local);
	}
	if (local->flag == 1 && local->finish == 0)
	{
		print_message(param, local->index + 1, SLEEP);
		usleep(param->time_sleep * 1000);
		local->flag = 0;
	}
}

void	*routine(void *arg)
{
	t_parameter	*param;
	t_local		local;

	param = ((t_index *)arg)->param;
	init_local(param, &local, ((t_index *)arg)->index);
	free(arg);
	if (param->must_eat == 0)
		return (print_message(param, local.index + 1, THINK), NULL);
	while (local.finish == 0)
	{
		pthread_mutex_lock(&param->dead);
		if (param->die == 1)
		{
			pthread_mutex_unlock(&param->dead);
			break ;
		}
		pthread_mutex_unlock(&param->dead);
		routine_helper(param, &local);
	}
	return (NULL);
}
