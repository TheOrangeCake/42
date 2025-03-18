/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:34:08 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/18 18:38:26 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_parameter		*param;
	int				i;
	long			current;
	struct timeval	time;

	param = (t_parameter *)arg;
	param->monitor_flag = 0;
	while (param->monitor_flag == 0)
	{
		gettimeofday(&time, NULL);
		current = time.tv_usec / 1000 + time.tv_sec * 1000;
		i = param->numb;
		while (--i >= 0)
		{
			if (current > param->timetable[i])
			{
				param->die = 1;
				param->monitor_flag = 1;
				printf("%10ld %5d died\n", current - param->start_time, i + 1);
				break ;
			}
		}
	}
}

int	join_thread(t_parameter *param, int i)
{
	while (--i >= 0)
	{
		if (pthread_join(param->philo[i], NULL) < 0)
			return (1);
	}
	param->monitor_flag = 1;
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
