/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:24:18 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/27 23:01:36 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	check_0(char *av[])
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (av[i] != NULL)
	{
		if (j == 0 && ft_atoi(av[i]) == 0)
			return (1);
		else if (ft_atoi(av[i]) == 0)
			j = 0;
		i++;
	}
	return (0);
}
