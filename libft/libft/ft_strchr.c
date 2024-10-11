/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:45:21 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/11 14:33:34 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0' && *s == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	test[] = "hello";
// 	char	test1[] = "hello";
// 	char	*result;
// 	char	*result1;

// 	result = ft_strchr(test, 'e');
// 	result1 = strchr(test1, 'e');
// 	if (result == NULL)
// 		printf("The result is NULL\n");
// 	else if (*result == '\0')
// 		printf("The result is Teminator\n");
// 	else
// 		printf("The remake result: %s\n", result);
// 	if (result1 == NULL)
// 		printf("The result is NULL\n");
// 	else if (*result1 == '\0')
// 		printf("The result is Teminator\n");
// 	else
// 		printf("The real result: %s\n", result1);
// 	return (0);
// }