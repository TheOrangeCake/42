/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:23:44 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/09 14:45:59 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr++;
		n--;
	}
	return (NULL);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	hello[] = "i am a cat";
// 	char	hello1[] = "i am a cat";
// 	char	*ptr;
// 	char	*ptr1;

// 	ptr = ft_memchr(hello, 'a', 3);
// 	ptr1 = memchr(hello1, 'a', 3);
// 	printf("Result: %s\n", ptr);
// 	printf("Result: %s\n", ptr1);
// 	return (0);
// }