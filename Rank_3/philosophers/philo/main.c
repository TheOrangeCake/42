/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:34:08 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/26 13:00:58 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor_helper(t_parameter *param, t_monitor *monitor)
{
	pthread_mutex_lock(&param->t[monitor->i]);
	if (param->timetable[monitor->i] == -1)
	{
		(monitor->count)++;
		param->timetable[monitor->i] = -2;
	}
	if (monitor->count == param->numb)
	{
		monitor->flag = 1;
		return (pthread_mutex_unlock(&param->t[monitor->i]), 1);
	}
	if (monitor->current > param->timetable[monitor->i]
		&& param->timetable[monitor->i] != -2)
	{
		pthread_mutex_lock(&param->dead);
		param->die = 1;
		monitor->flag = 1;
		pthread_mutex_unlock(&param->dead);
		printf("%10ld %5d died\n",
			monitor->current - param->start_time, monitor->i + 1);
		return (pthread_mutex_unlock(&param->t[monitor->i]), 1);
	}
	pthread_mutex_unlock(&param->t[monitor->i]);
	return (0);
}

void	*monitor(void *arg)
{
	t_parameter		*param;
	t_monitor		monitor;

	monitor.count = 0;
	param = (t_parameter *)arg;
	monitor.flag = 0;
	while (monitor.flag == 0)
	{
		gettimeofday(&monitor.time, NULL);
		monitor.current = monitor.time.tv_usec
			/ 1000 + monitor.time.tv_sec * 1000;
		monitor.i = param->numb;
		while (--monitor.i >= 0)
		{
			if (monitor_helper(param, &monitor) == 1)
				break ;
		}
	}
	return (NULL);
}

int	join_thread(t_parameter *param, int i)
{
	while (--i >= 0)
	{
		if (pthread_join(param->philo[i], NULL) < 0)
			return (1);
	}
	if (pthread_join(param->monitor, NULL) < 0)
		return (1);
	return (0);
}

int	run(t_parameter *param)
{
	int		i;
	t_index	*index;

	gettimeofday(&param->time, NULL);
	param->start_time = param->time.tv_usec
		/ 1000 + param->time.tv_sec * 1000;
	i = -1;
	while (++i < param->numb)
		param->timetable[i] = param->start_time + param->time_die;
	if (pthread_create(&param->monitor, NULL, &monitor, param) < 0)
		return (free_all(param), 1);
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
	if (join_thread(param, i) != 0)
		return (free_all(param), 1);
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
			if (init_rest(&param) != 0 || run(&param) != 0)
				return (printf("Error\n"), 1);
		}
	}
	else
		return (printf("Input Error\n"), 1);
	return (0);
}
