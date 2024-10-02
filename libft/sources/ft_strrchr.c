/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:48:16 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/02 21:48:16 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	const char	*ptr;

	i = 0;
	while (*s)
	{
		if (*s == c)
		{
			ptr = s;
			i = 1;
		}
		s++;
	}
	if (i == 1)
		return ((char *)ptr);
	else if (c == '\0' && *s == '\0')
		return ((char *)s);
	else
		return (NULL);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	test[] = "I am a cat";
// 	char	test1[] = "I am a cat";
// 	char	*result;
// 	char	*result1;

// 	result = ft_strrchr(test, 'm');
// 	result1 = strrchr(test1, 'm');
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