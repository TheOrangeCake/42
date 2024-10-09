/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:34:56 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/09 18:02:20 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptrdest;
	unsigned char	*ptrsrc;

	ptrdest = (unsigned char *)dest;
	ptrsrc = (unsigned char *)src;
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
	char	test[] = "\0";
	char	test1[] = "\0";
	char	test2[] = "\0";
	char	test3[]= "\0";

	memcpy(test, test1, 3);
	// ft_memcpy(test2, test3, 3);
	printf("The result is %s\n", test);
	// printf("The result is %s\n", test2);
	return (0);
}