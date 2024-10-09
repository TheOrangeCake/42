/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:48:27 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/09 14:38:38 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	hello[50] = "hello, i am a cat";
// 	char	hello1[50] = "hello, i am a cat";

// 	printf("The result is %zu\n", strlen(hello));
// 	printf("The result is %zu\n", ft_strlen(hello1));
// 	return (0);
// }