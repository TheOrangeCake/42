/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_of_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:27:55 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/17 15:37:04 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*case_of_one_next(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	gettimeofday(&philo.t, NULL);
	printf("%ld 1 has taken the front fork\n", philo.t.tv_usec
		/ 1000 + philo.t.tv_sec * 1000);
	usleep(philo.die * 1000);
	gettimeofday(&philo.t, NULL);
	printf("%ld 1 died\n", philo.t.tv_usec / 1000 + philo.t.tv_sec * 1000);
	return (NULL);
}

int	case_of_one(t_philo philo)
{
	philo.single = malloc(sizeof(pthread_t) * philo.numb);
		if (philo.single == NULL)
		return (1);
	if (pthread_create(&philo.single[0], NULL, &case_of_one_next, &philo) != 0)
	{
		free(philo.single);
		return (1);
	}
	if (pthread_join(philo.single[0], NULL) != 0)
	{
		free(philo.single);
		return (1);
	}
	free(philo.single);
	return (0);
}
