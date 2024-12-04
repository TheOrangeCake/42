/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:59:53 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/04 14:52:57 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include <stdio.h>

int	input_check(char *av[])
{
	int	i;
	int	j;
	int	k;

	i = 1;
	while (av[i] != NULL)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if ((av[i][j] < '0' || av[i][j] > '9') && (av[i][j] != ' '
					&& av[i][j] != '-' && av[i][j] != '+'))
				return (1);
			j++;
		}
		k = i + 1;
		while (av[k] != NULL)
		{
			if (ft_strcmp(av[i], av[k]) == 0)
				return (1);
			k++;
		}
		i++;
	}
	return (0);
}

t_pile	initiate_a(char *av[])
{
	t_pile	*a;
	t_pile	head;

}

// void	push_swap(char *av[])
// {

// }

int	main(int ac, char *av[])
{
	t_pile	a;

	if (ac > 1)
	{
		if (input_check(av) == 1)
			return (write(2, "input error\n", 12), 0);
		else
			a = initiate_a(av);
		// push_swap(av);
	}
	else if (ac == 1)
	{
		printf("placeholder\n");
	}
	return (0);
}
