/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:34:08 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/13 12:24:43 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av)
{
	t_philo	philo;

	if (ac == 5 || ac == 6)
	{
		philo.n_philo = ft_atoi(av[1]);
		philo.die = ft_atoi(av[2]);
		philo.eat = ft_atoi(av[3]);
		philo.sleep = ft_atoi(av[4]);
		if (ac == 6)
			philo.must_eat = ft_atoi(av[5]);
		else
			philo.must_eat = -1;
	}
	else
		return (printf("Wrong number of input\n"), 1);
	return (0);
}
