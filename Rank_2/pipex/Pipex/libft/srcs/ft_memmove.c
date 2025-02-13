/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:07:26 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/11 13:51:42 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptrdest;
	unsigned char	*ptrsrc;

	ptrdest = (unsigned char *)dest;
	ptrsrc = (unsigned char *)src;
	if (ptrdest == NULL || ptrsrc == NULL)
		return (NULL);
	if (ptrdest < ptrsrc)
	{
		while (n > 0)
		{
			*ptrdest++ = *ptrsrc++;
			n--;
		}
	}
	else
	{
		while (n > 0)
		{
			*(ptrdest + n - 1) = *(ptrsrc + n - 1);
			n--;
		}
	}
	return (dest);
}

// #include <stdio.h>

// int	main()
// {
//     char	src[] = "Hello, World!";
// 	char	src1[] = "Hello, World!";

//     printf("before memmove: %s\n", src);
// 	printf("before memmove: %s\n", src1);
//     ft_memmove(src + 7, src, 6);
// 	memmove(src1 + 7, src1, 6);
//     printf("after memmove: %s\n", src);
// 	printf("after memmove: %s\n", src1);
//     strcpy(src, "Hello, World!");
// 	strcpy(src1, "Hello, World!");
//     printf("before memmove: %s\n", src);
// 	printf("before memmove: %s\n", src1);
//     ft_memmove(src, src + 7, 6);
// 	memmove(src1, src1 + 7, 6);
//     printf("after memmove: %s\n", src);
// 	printf("after memmove: %s\n", src1);
//     return (0);
// }