/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:51:10 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/18 12:10:55 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_parameter *params, int index, int code)
{
	long	current_time;

	gettimeofday(&params->time, NULL);
	current_time = params->time.tv_usec
		/ 1000 + params->time.tv_sec * 1000;
	if (code == 1)
		printf("%10ld %5d is thinking\n",
			current_time - params->start_time, index);
	else if (code == 2)
		printf("%10ld %5d has taken the front fork\n",
			current_time - params->start_time, index);
	else if (code == 3)
		printf("%10ld %5d has taken the left fork\n",
			current_time - params->start_time, index);
	else if (code == 4)
		printf("%10ld %5d is eating\n",
			current_time - params->start_time, index);
	else if (code == 5)
		printf("%10ld %5d is sleeping\n",
			current_time - params->start_time, index);
	else if (code == 6)
		printf("%10ld %5d died\n",
			current_time - params->start_time, index);
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

int	init_parameters(t_parameter *params, char **av, int ac)
{
	params->numb = ft_atoi(av[1]);
	params->time_die = ft_atoi(av[2]);
	params->time_eat = ft_atoi(av[3]);
	params->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		params->must_eat = ft_atoi(av[5]);
	else
		params->must_eat = 0;
	if (params->numb == 0 || params->time_die > 2147483647
		|| params->time_eat > 2147483647
		|| params->time_sleep > 2147483647
		|| params->must_eat > 2147483647)
		return (1);
	return (0);
}
