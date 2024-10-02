/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:47:31 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/02 22:47:31 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = ((unsigned char *)s1);
	ptr2 = ((unsigned char *)s2);
	while (n > 0)
	{
		if (*ptr1 != *ptr2)
			return (*ptr1 - *ptr2);
		ptr1++;
		ptr2++;
		n--;
	}
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	test[] = "cat";
// 	char	test1[] = "aat";
// 	char	test2[] = "cat";
// 	char	test3[] = "aat";

// 	printf("The result: %d\n", ft_memcmp(test, test1, 3));
// 	printf("The result: %d\n", memcmp(test2, test3, 3));
// 	return (0);
// }