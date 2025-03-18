/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:34:08 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/18 13:07:02 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	init_philo(t_parameter *params)
// {
// 	int	i;

// 	i = 0;
// 	while (++i < params->numb)
// 	{
// 		params->fork[i] = 
// 	}
// }

int	malloc_all(t_parameter *params)
{
	int	i;

	params->philo = ft_calloc(params->numb, sizeof(pthread_t));
	if (params->philo == NULL)
		return (1);
	// if (init_philo(params) != 0)
	// 	return (free(params->fork), free(params->philo), 1);
	params->mutex = ft_calloc(params->numb, sizeof(pthread_mutex_t));
	if (params->mutex == NULL)
		return (free(params->philo), 1);
	i = -1;
	while (++i < params->numb)
	{
		if (pthread_mutex_init(&params->mutex[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&params->mutex[i]);
			return (free(params->mutex), free(params->philo), 1);
		}
	}
	return (0);
}

void	takefork(t_parameter *params, int index, int *flag)
{
	int	left_fork;

	if (index == 0)
		left_fork = params->numb - 1;
	else
		left_fork = index - 1;
	pthread_mutex_lock(&params->mutex[index]);
	print_message(params, index + 1, F_FORK);
	pthread_mutex_lock(&params->mutex[left_fork]);
	print_message(params, index + 1, L_FORK);
	print_message(params, index + 1, EAT);
	usleep(params->time_eat * 1000);
	*flag = 1;
	pthread_mutex_unlock(&params->mutex[index]);
	pthread_mutex_unlock(&params->mutex[left_fork]);
	
}

void	*routine(void *arg)
{
	t_parameter	*params;
	int			index;
	int			flag;

	flag = 0;
	params = ((t_index *)arg)->params;
	index = ((t_index *)arg)->index;
	free(arg);
	while (1)
	{
		print_message(params, index + 1, THINK);
		takefork(params, index, &flag);
		if (flag == 1)
		{
			print_message(params, index + 1, SLEEP);
			usleep(params->time_sleep* 1000);
			flag = 0;
		}
	}
	return (NULL);
}

int	run(t_parameter *params)
{
	int		i;
	t_index	*index;

	if (malloc_all(params) != 0)
		return (1);
	gettimeofday(&params->time, NULL);
	params->start_time = params->time.tv_usec
		/ 1000 + params->time.tv_sec * 1000;
	i = -1;
	while (++i < params->numb)
	{
		index = calloc(1, sizeof(t_index));
		if (index == NULL)
			return (free_all(params), 1);
		index->index = i;
		index->params = params;
		if (pthread_create(&params->philo[i], NULL, &routine, index) < 0)
			return (free_all(params), 1);
	}
	while (--i >= 0)
	{
		if (pthread_join(params->philo[i], NULL) < 0)
			return (free_all(params), 1);
	}
	return (free_all(params), 0);
}

int	main(int ac, char **av)
{
	t_parameter	params;

	if (ac == 5 || ac == 6)
	{
		if (input_check(av) == 1)
			return (printf("Input Error\n"), 1);
		if (init_parameters(&params, av, ac) == 1)
			return (printf("Input Error\n"), 1);
		if (params.numb == 1)
		{
			if (case_of_one(&params) != 0)
				return (printf("Error\n"), 1);
		}
		else
		{
			if (run(&params) != 0)
				return (printf("Error\n"), 1);
		}
	}
	else
		return (printf("Input Error\n"), 1);
	return (0);
}
