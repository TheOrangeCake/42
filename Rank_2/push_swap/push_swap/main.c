/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:59:53 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/04 12:18:19 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	input_check(char *av[])
{
	return (0);
}

// void	push_swap(char *av[])
// {
	
// }

int	main(int ac, char *av[])
{
	if (ac > 0)
	{
		if (input_check(av) == 1)
			return (write(2, "input error\n", 12), 0);
		// push_swap(av);
	}
	else if (ac == 0)
	{
		ft_printf("placeholder");
	}
	return (0);
}
