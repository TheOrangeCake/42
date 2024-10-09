/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:37:23 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/09 14:38:00 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 176)
		return (16384);
	else
		return (0);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int	a;
// 	int	b;

// 	a = '9';
// 	b = '9';
// 	printf("The result is %d\n", isprint(a));
// 	printf("The result is %d\n", ft_isprint(b));
// 	return (0);
// }