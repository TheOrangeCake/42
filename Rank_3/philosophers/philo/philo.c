/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:27:14 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/20 19:13:42 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	takefork_left(t_parameter *param, t_local *local)
{
	int	left_fork;

	if (local->index == 0)
		left_fork = param->numb - 1;
	else
		left_fork = local->index - 1;
	pthread_mutex_lock(&param->mutex[left_fork]);
	print_message(param, local->index + 1, L_FORK);
	pthread_mutex_lock(&param->mutex[local->index]);
	print_message(param, local->index + 1, F_FORK);
	print_message(param, local->index + 1, EAT);
	gettimeofday(&local->time, NULL);
	local->last_eat = local->time.tv_usec / 1000 + local->time.tv_sec * 1000;
	param->timetable[local->index] = local->last_eat + param->time_die;
	usleep(param->time_eat * 1000);
	local->eaten++;
	local->flag = 1;
	pthread_mutex_unlock(&param->mutex[local->index]);
	pthread_mutex_unlock(&param->mutex[left_fork]);
	if (local->eaten == param->must_eat)
		local->finish = 1;
}

void	takefork(t_parameter *param, t_local *local)
{
	int	left_fork;

	if (local->index == 0)
		left_fork = param->numb - 1;
	else
		left_fork = local->index - 1;
	pthread_mutex_lock(&param->mutex[local->index]);
	print_message(param, local->index + 1, F_FORK);
	pthread_mutex_lock(&param->mutex[left_fork]);
	print_message(param, local->index + 1, L_FORK);
	print_message(param, local->index + 1, EAT);
	gettimeofday(&local->time, NULL);
	local->last_eat = local->time.tv_usec / 1000 + local->time.tv_sec * 1000;
	param->timetable[local->index] = local->last_eat + param->time_die;
	usleep(param->time_eat * 1000);
	local->eaten++;
	local->flag = 1;
	pthread_mutex_unlock(&param->mutex[local->index]);
	pthread_mutex_unlock(&param->mutex[left_fork]);
	if (local->eaten == param->must_eat)
	{
		local->finish = 1;
		param->timetable[local->index] = -1;
	}
}

void	*routine(void *arg)
{
	t_parameter	*param;
	t_local		local;

	init_local(param, &local);
	param = ((t_index *)arg)->param;
	local.index = ((t_index *)arg)->index;
	free(arg);
	if (param->must_eat == 0)
		return (print_message(param, local.index + 1, THINK), NULL);
	while (local.finish == 0)
	{
		if (param->die == 1)
			break ;
		print_message(param, local.index + 1, THINK);
		if (local.index % 2 == 0)
			takefork(param, &local);
		else
			takefork_left(param, &local);
		if (local.flag == 1)
		{
			print_message(param, local.index + 1, SLEEP);
			usleep(param->time_sleep * 1000);
			local.flag = 0;
		}
	}
}
