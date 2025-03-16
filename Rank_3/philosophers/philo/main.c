/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:34:08 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/16 11:16:24 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo, int i)
{
	philo->fork[i] = 0;
	showtime();
	printf(" %d has taken the front fork\n", i);
	if (i == 0)
	{
		philo->fork[philo->numb] = 0;
		showtime();
		printf(" %d has taken the left fork\n", i);
	}
	else
	{
		philo->fork[i - 1] = 0;
		showtime();
		printf(" %d has taken the left fork\n", i);
	}
	showtime();
	printf(" %d is eating\n", i);
	usleep(philo->eat * 1000);
	philo->fork[1] = 1;
	if (i == 0)
		philo->fork[philo->numb] = 1;
	else
		philo->fork[i - 1] = 1;
}

void	*philo_thread(void *arg)
{
	t_philo	philo;
	int		i;
	int		flag;

	philo = *(t_philo *)arg;
	i = philo.i;
	flag = 0;
	while (1)
	{
		pthread_mutex_lock(&philo.mutex);
		flag = 1;
		take_fork(&philo, i);
		pthread_mutex_unlock(&philo.mutex);
		if (flag == 1)
		{
			showtime();
			printf(" %d is sleeping\n", i);
			usleep(philo.sleep * 1000);
			flag = 0;
		}
		showtime();
		printf(" %d is thinking\n", i);
	}
}

int	run(t_philo philo)
{
	pthread_t	a_philo[philo.numb];
	int	*a;

	philo.fork = malloc(sizeof(int) * philo.numb);
	if (philo.fork == NULL)
		return (1);
	philo.i = 0;
	while (philo.i < philo.numb)
		philo.fork[philo.i++] = 1;
	pthread_mutex_init(&philo.mutex, NULL);
	philo.i = 0;
	while (philo.i < philo.numb)
	{
		if (pthread_create(&a_philo[philo.i], NULL, &philo_thread, &philo) != 0)
			return (free(philo.fork), 1);
		philo.i++;
	}
	philo.j = 0;
	while (philo.j < philo.numb)
	{
		if (pthread_join(a_philo[philo.j], NULL) != 0)
			return (free(philo.fork), 1);
		philo.j++;
	}
	pthread_mutex_destroy(&philo.mutex);
	free(philo.fork);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo			philo;

	if (ac == 5 || ac == 6)
	{
		philo.numb = ft_atoi(av[1]);
		philo.die = ft_atoi(av[2]);
		philo.eat = ft_atoi(av[3]);
		philo.sleep = ft_atoi(av[4]);
		if (ac == 6)
			philo.must_eat = ft_atoi(av[5]);
		else
			philo.must_eat = -1;
		if (philo.numb == 1)
		{
			if (case_of_one(philo) != 0)
				return (printf("Error\n"), 1);
		}
		else
		{
			if (run(philo) < 0)
				return (printf("Error\n"), 1);
		}
	}
	else
		return (printf("Wrong number of input\n"), 1);
	return (0);
}
