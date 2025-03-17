/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:34:08 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/17 22:47:38 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_all(t_parameter *params)
{
	int	i;

	params->philo->fork = ft_calloc(params->numb, sizeof(int));
	if (params->philo->fork == NULL)
		return (1);
	params->philo->single = ft_calloc(params->numb, sizeof(pthread_t));
	if (params->philo->single == NULL)
		return (free(params->philo->fork), 1);
	params->philo->mutex = ft_calloc(params->numb, sizeof(pthread_mutex_t));
	if (params->philo->mutex == NULL)
		return (free(params->philo->fork), free(params->philo->single), 1);
	i = -1;
	while (++i < params->numb)
	{
		if (pthread_mutex_init(&params->philo->mutex[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&params->philo->mutex[i]);
			return (free(params->philo->mutex), free(params->philo->fork),
				free(params->philo->single), 1);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo		philo;
	t_parameter	params;

	if (ac == 5 || ac == 6)
	{
		params.philo = &philo;
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
			if (malloc_all(&params) != 0)
				return (printf("Error\n"), 1);
		}
	}
	else
		return (printf("Input Error\n"), 1);
	return (0);
}
