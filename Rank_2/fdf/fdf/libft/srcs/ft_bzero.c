/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:22:14 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/09 14:39:39 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = '\0';
		n--;
		ptr++;
	}
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	test[6] = "hello";
// 	char	test1[6] = "hello";

// 	bzero(test, 3);
// 	ft_bzero(test1, 3);
// 	printf("The result is %s\n", test);
// 	printf("The result is %s\n", test1);
// 	return (0);
// }