/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:07:17 by hoannguy          #+#    #+#             */
/*   Updated: 2024/09/29 16:07:17 by hoannguy         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char test1[50] = "12346";
// 	char test2[50] = "12345";
// 	char test3[50] = "12346";
// 	char test4[50] = "12345";

// 	printf("new function: %d\n", ft_strcmp(test1, test2));
// 	printf("old function: %d\n", strcmp(test3, test4));
// 	return (0);
// }
