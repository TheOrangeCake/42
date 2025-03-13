/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_of_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:27:55 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/13 18:02:14 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*case_of_one_next(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	tofday(&philo.t, NULL);
	printf("%ld 1 is thinking\n", philo.t.tv_usec
		/ 1000 + philo.t.tv_sec * 1000);
	usleep(philo.die * 1000);
	tofday(&philo.t, NULL);
	printf("%ld 1 died\n", philo.t.tv_usec / 1000 + philo.t.tv_sec * 1000);
	return (NULL);
}

int	case_of_one(t_philo philo)
{
	philo.a_philo = malloc(sizeof(int) * philo.numb);
		if (philo.a_philo == NULL)
		return (1);
	if (pthread_create(&a_philo[0], NULL, &case_of_one_next, &philo) != 0)
	{
		free(philo.a_philo);
		return (1);
	}
	if (pthread_join(a_philo[0], NULL) != 0)
	{
		free(philo.a_philo);
		return (1);
	}
	free(philo.a_philo);
	return (0);
}
