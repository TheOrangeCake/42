/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:34:08 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/18 15:46:51 by hoannguy         ###   ########.fr       */
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
	usleep(param->time_eat * 1000);
	local->eaten++;
	local->flag = 1;
	// local->time = gettimeofday(&local->time, NULL);
	// local->last_eat = local->time.tv_usec / 1000 + local->time.tv_sec * 1000;
	// local->expected_dead = local->last_eat + param->time_die;
	pthread_mutex_unlock(&param->mutex[local->index]);
	pthread_mutex_unlock(&param->mutex[left_fork]);
	if (param->must_eat > 0 && local->eaten == param->must_eat)
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
	usleep(param->time_eat * 1000);
	local->eaten++;
	local->flag = 1;
	// local->time = gettimeofday(&local->time, NULL);
	// local->last_eat = local->time.tv_usec / 1000 + local->time.tv_sec * 1000;
	// local->expected_dead = local->last_eat + param->time_die;
	pthread_mutex_unlock(&param->mutex[local->index]);
	pthread_mutex_unlock(&param->mutex[left_fork]);
	if (param->must_eat > 0 && local->eaten == param->must_eat)
		local->finish = 1;
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
	while (param->die == 0 && local.finish == 0)
	{
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
	return (NULL);
}

int	run(t_parameter *param)
{
	int		i;
	t_index	*index;

	if (init_rest(param) != 0)
		return (1);
	gettimeofday(&param->time, NULL);
	param->start_time = param->time.tv_usec
		/ 1000 + param->time.tv_sec * 1000;
	i = -1;
	while (++i < param->numb)
	{
		index = calloc(1, sizeof(t_index));
		if (index == NULL)
			return (free_all(param), 1);
		index->index = i;
		index->param = param;
		if (pthread_create(&param->philo[i], NULL, &routine, index) < 0)
			return (free_all(param), 1);
	}
	while (--i >= 0)
	{
		if (pthread_join(param->philo[i], NULL) < 0)
			return (free_all(param), 1);
	}
	return (free_all(param), 0);
}

int	main(int ac, char **av)
{
	t_parameter	param;

	if (ac == 5 || ac == 6)
	{
		if (input_check(av) == 1)
			return (printf("Input Error\n"), 1);
		if (init_parameters(&param, av, ac) == 1)
			return (printf("Input Error\n"), 1);
		if (param.numb == 1)
		{
			if (case_of_one(&param) != 0)
				return (printf("Error\n"), 1);
		}
		else
		{
			if (run(&param) != 0)
				return (printf("Error\n"), 1);
		}
	}
	else
		return (printf("Input Error\n"), 1);
	return (0);
}
