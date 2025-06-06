/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:59:41 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/11 14:45:15 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s2 && n > 0)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	if ((*s1 || *s2) && n > 0)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}

// #include <stdio.h>

// int main()
// {
// 	char	str1[50] = "test\200";
// 	char	str2[50] = "test\0";
// 	// char	str3[50] = "hell";
// 	// char	str4[50] = "heulo";
// 	char	str11[50] = "test\200";
// 	char	str22[50] = "test\0";
// 	// char	str33[50] = "hell";
// 	// char	str44[50] = "heulo";
//     int test1a = ft_strncmp(str1, str2, 6);
//     int test1b = strncmp(str11, str22, 6);
//     printf("test 1: hello, , 2\nn: %d\no: %d\n", test1a, test1b);	
//     // int test2a = ft_strncmp(str11, str11, 10);
//     // int test2b = strncmp(str11, str11, 10);
//     // printf("test 2: hello, hello, 10,\nn: %d\no: %d\n", test2a, test2b);
//     // int test3a = ft_strncmp(str11, str33, 4);
//     // int test3b = strncmp(str11, str33, 4);
//     // printf("test 3: hello, hell, 4, \nn: %d\no: %d\n", test3a, test3b);
// 	// int test4a = ft_strncmp(str1, str3, 5);
// 	// int test4b = strncmp(str11, str33, 5);
// 	// printf("test 4: hello, hell, 5,\nn: %d\no: %d\n", test4a, test4b);
// 	return(0);
// }