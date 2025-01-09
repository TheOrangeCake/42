/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 18:05:25 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/06 23:45:11 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	nb;

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

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char	new[] = "   -1234";
// 	char	old[] = "   -1234";

// 	printf("New: %d\n", ft_atoi(new));
// 	printf("Old: %d\n", atoi(old));
// 	return (0);
// }