/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:02:46 by hoannguy          #+#    #+#             */
/*   Updated: 2024/09/29 16:02:54 by hoannguy         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	a;

	a = 0;
	while (*str != '\0')
	{
		a++;
		str++;
	}
	return (a);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	test[50] = "Hello, it's a cat";

// 	printf("The string \"%s\" has %d letters\n", test, ft_strlen(test));
// 	return (0);
// }