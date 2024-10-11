/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:34:56 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/11 13:11:06 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptrdest;
	unsigned char	*ptrsrc;

	ptrdest = (unsigned char *)dest;
	ptrsrc = (unsigned char *)src;
	// if (ptrdest == NULL || ptrsrc == NULL)
	// 	return (dest);
	while (n > 0)
	{
		*ptrdest = *ptrsrc;
		ptrdest++;
		ptrsrc++;
		n--;
	}
	return (dest);
}

#include <stdio.h>

int	main(void)
{
	char	*testnul;
	char	*testnul1;
	char	*testnul2;
	char	*testnul3;
	char	test[] = "hello";
	char	test1[] = "world";
	char	test2[] = "hello";
	char	test3[]= "world";

	testnul = NULL;
	testnul1 = NULL;
	testnul2 = NULL;
	testnul3 = NULL;
	memcpy(test, test1, 1);
	ft_memcpy(test2, test3, 1);
	printf("The result is %s\n", test);
	printf("The result is %s\n", test2);
	memcpy(testnul, testnul1, 1);
	ft_memcpy(testnul2, testnul3, 1);
	printf("The result is %s\n", testnul);
	printf("The result is %s\n", testnul2);
	return (0);
}