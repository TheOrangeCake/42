/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:34:08 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/17 16:04:08 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo, int i)
{
	philo->fork[i] = 1;
	gettimeofday(&philo->t, NULL);
	printf("%ld %d has taken the front fork\n", philo->t.tv_usec
		/ 1000 + philo->t.tv_sec * 1000, i + 1);
	if (i == 0)
		philo->fork[philo->numb - 1] = 1;
	else
		philo->fork[i - 1] = 1;
	gettimeofday(&philo->t, NULL);
	printf("%ld %d has taken the left fork\n", philo->t.tv_usec
		/ 1000 + philo->t.tv_sec * 1000, i + 1);
	gettimeofday(&philo->t, NULL);
	printf("%ld %d is eating\n", philo->t.tv_usec
		/ 1000 + philo->t.tv_sec * 1000, i + 1);
	usleep(philo->eat * 1000);
	philo->fork[i] = 0;
	if (i == 0)
		philo->fork[philo->numb - 1] = 0;
	else
		philo->fork[i - 1] = 0;
}

void	*philo_thread(void *arg)
{
	t_wrapper	*wrapper;
	t_philo	*philo;
	int		i;
	int		flag;

	wrapper = (t_wrapper *)arg;
	philo = wrapper->philo;
	i = wrapper->index;
	flag = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex[i]);
		if (i == 0)
			pthread_mutex_lock(&philo->mutex[philo->numb - 1]);
		else
			pthread_mutex_lock(&philo->mutex[i - 1]);
		flag = 1;
		take_fork(philo, i);
		pthread_mutex_unlock(&philo->mutex[i]);
		if (i == 0)
			pthread_mutex_unlock(&philo->mutex[philo->numb - 1]);
		else
			pthread_mutex_unlock(&philo->mutex[i - 1]);
		if (flag == 1)
		{
			gettimeofday(&philo->t, NULL);
			printf("%ld %d is sleeping\n", philo->t.tv_usec
				/ 1000 + philo->t.tv_sec * 1000, i + 1);
			usleep(philo->sleep * 1000);
			flag = 0;
		}
		gettimeofday(&philo->t, NULL);
		printf("%ld %d is thinking\n", philo->t.tv_usec
		/ 1000 + philo->t.tv_sec * 1000, i + 1);
	}
	free(wrapper);
}

int	run(t_philo philo)
{
	t_wrapper	*wrapper;
	
	philo.fork = ft_calloc(philo.numb, sizeof(int));
	if (philo.fork == NULL)
		return (1);
	philo.single = ft_calloc(philo.numb, sizeof(pthread_t));
	if (philo.single == NULL)
		return (free(philo.fork), 1);
	philo.mutex = malloc(sizeof(pthread_mutex_t) * philo.numb);
	if (philo.mutex == NULL)
		return (free(philo.fork), free(philo.single), 1);
	philo.i = 0;
	while (philo.i < philo.numb)
	{
		pthread_mutex_init(&philo.mutex[philo.i], NULL);
		philo.i++;
	}
	philo.i = 0;
	while (philo.i < philo.numb)
	{
		wrapper = malloc(sizeof(t_wrapper));
		if (wrapper == NULL)
			return (free(philo.fork), free(philo.single), 1);
		wrapper->philo = &philo;
		wrapper->index = philo.i;
		if (pthread_create(&philo.single[philo.i], NULL, &philo_thread, wrapper) != 0)
			return (free(philo.fork), free(philo.single), 1);
		philo.i++;
	}
	philo.j = 0;
	while (philo.j < philo.numb)
	{
		if (pthread_join(philo.single[philo.j], NULL) != 0)
			return (free(philo.fork), free(philo.single), 1);
		philo.j++;
	}
	// pthread_mutex_destroy(&philo.mutex);
	philo.i = 0;
	while (philo.i < philo.numb)
	{
		pthread_mutex_destroy(&philo.mutex[philo.i]);
		philo.i++;
	}
	free(philo.mutex);
	free(philo.single);
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
