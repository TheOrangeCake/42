/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:47:19 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/11 12:53:55 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	bit_count(long n)
{
	int		count;

	count = 0;
	if (n < 0)
		n = -n;
	if (n == 0)
		count = 1;
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*malloc_itoa(long n, long count)
{
	char	*ptr;
	long	sign;

	sign = n;
	if (sign >= 0)
		ptr = malloc(sizeof(char) * (count + 1));
	if (sign < 0)
		ptr = malloc(sizeof(char) * (count + 2));
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}

static char	*exception(char *ptr)
{
	ptr[0] = '0';
	return (ptr);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*ptr;
	long	i;

	i = n;
	count = bit_count(i);
	ptr = malloc_itoa(i, count);
	if (ptr == NULL)
		return (NULL);
	if (i == 0)
		ptr = exception(ptr);
	if (i < 0)
	{
		ptr[0] = '-';
		i = -i;
		count = count + 1;
	}
	ptr[count--] = '\0';
	while (i > 0)
	{
		ptr[count--] = i % 10 + '0';
		i = i / 10;
	}
	return (ptr);
}

// #include <stdio.h>

// int main()
// {
//     printf("resutl: %s\n", ft_itoa(0));
// 	printf("resutl: %s\n", ft_itoa(42));
// 	printf("resutl: %s\n", ft_itoa(-42));
// 	printf("resutl: %s\n", ft_itoa(-2147483648));
// 	printf("resutl: %s\n", ft_itoa(2147483647));
//     return (0);
// }