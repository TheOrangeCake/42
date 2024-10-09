/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:24:31 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/09 14:37:16 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (8);
	else
		return (0);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int	a;
// 	int	b;

// 	a = ' ';
// 	b = ' ';
// 	printf("The result is %d\n", isalnum(a));
// 	printf("The result is %d\n", ft_isalnum(b));
// 	return (0);
// }