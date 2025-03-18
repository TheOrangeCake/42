/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:51:10 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/18 15:46:01 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_parameter *param, int index, int code)
{
	long	current_time;

	gettimeofday(&param->time, NULL);
	current_time = param->time.tv_usec
		/ 1000 + param->time.tv_sec * 1000;
	pthread_mutex_lock(param->p);
	if (code == 1)
		printf("%10ld %5d is thinking\n",
			current_time - param->start_time, index);
	else if (code == 2)
		printf("%10ld %5d has taken the front fork\n",
			current_time - param->start_time, index);
	else if (code == 3)
		printf("%10ld %5d has taken the left fork\n",
			current_time - param->start_time, index);
	else if (code == 4)
		printf("%10ld %5d is eating\n",
			current_time - param->start_time, index);
	else if (code == 5)
		printf("%10ld %5d is sleeping\n",
			current_time - param->start_time, index);
	else if (code == 6)
		printf("%10ld %5d died\n",
			current_time - param->start_time, index);
	pthread_mutex_unlock(param->p);
}

int	input_check(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i] != NULL)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if ((av[i][j] < '0' || av[i][j] > '9') && av[i][j] != '+')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	init_local(t_parameter *param, t_local *local)
{
	local->flag = 0;
	local->eaten = 0;
	local->finish = 0;
	// local->last_eat = param->start_time;
	// local->expected_dead = local->last_eat + param->time_die;
}

int	init_rest(t_parameter *param)
{
	int	i;

	param->philo = ft_calloc(param->numb, sizeof(pthread_t));
	if (param->philo == NULL)
		return (1);
	param->mutex = ft_calloc(param->numb, sizeof(pthread_mutex_t));
	if (param->mutex == NULL)
		return (free(param->philo), 1);
	param->p = ft_calloc(1, sizeof(pthread_mutex_t));
	if (param->p == NULL)
		return (free(param->philo), free(param->mutex), 1);
	if (pthread_mutex_init(param->p, NULL) != 0)
		return (free(param->mutex), free(param->philo), 1);
	i = -1;
	while (++i < param->numb)
	{
		if (pthread_mutex_init(&param->mutex[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&param->mutex[i]);
			pthread_mutex_destroy(param->p);
			return (free(param->p), free(param->mutex), free(param->philo), 1);
		}
	}
	return (0);
}

int	init_parameters(t_parameter *param, char **av, int ac)
{
	param->numb = ft_atoi(av[1]);
	param->time_die = ft_atoi(av[2]);
	param->time_eat = ft_atoi(av[3]);
	param->time_sleep = ft_atoi(av[4]);
	param->die = 0;
	if (ac == 6)
		param->must_eat = ft_atoi(av[5]);
	else
		param->must_eat = -1;
	if (param->numb == 0 || param->time_die > 2147483647
		|| param->time_eat > 2147483647
		|| param->time_die <= 0
		|| param->time_sleep > 2147483647
		|| param->must_eat > 2147483647)
		return (1);
	return (0);
}
