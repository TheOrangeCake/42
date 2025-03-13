/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:15:02 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/13 17:53:09 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	showtime(void)
{
	struct timeval	t;
	
	tofday(&t, NULL);
	printf("%ld ", t.tv_usec / 1000 + t.tv_sec * 1000);
}

long	ft_atoi(char *nptr)
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
