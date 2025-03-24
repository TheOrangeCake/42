/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:15:02 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/24 12:10:57 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_parameter *param)
{
	int	i;

	i = -1;
	while (++i < param->numb)
		pthread_mutex_destroy(&param->mutex[i]);
	i = -1;
	while (++i < param->numb)
		pthread_mutex_destroy(&param->t[i]);
	pthread_mutex_destroy(&param->p);
	pthread_mutex_destroy(&param->dead);
	free(param->t);
	free(param->mutex);
	free(param->timetable);
	free(param->philo);
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

long	ft_atoi(const char *nptr)
{
	long	sign;
	long	nb;

	nb = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
	{
		sign = -sign;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb * 10 + *nptr - '0';
		nptr++;
	}
	return (nb * sign);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	total_size;

	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	while (total_size > 0)
	{
		ptr[total_size - 1] = 0;
		total_size--;
	}
	return ((void *)ptr);
}
