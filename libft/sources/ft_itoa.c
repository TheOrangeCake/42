/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:47:19 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/09 12:09:01 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	bit_count(int n)
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

static char	*malloc_itoa(int n, int count)
{
	char	*ptr;
	int		sign;

	sign = n;
	if (sign >= 0)
		ptr = malloc(sizeof(char) * count + 1);
	if (sign < 0)
		ptr = malloc(sizeof(char) * count + 2);
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}

static char	*exception(char *ptr, int n)
{
	int	i;

	if (n == 0)
	{
		ptr[0] = '0';
		ptr[1] = '\0';
	}
	if (n == -2147483648)
	{
		ptr[0] = '-';
		ptr[1] = '2';
		ptr[2] = '1';
		ptr[3] = '4';
		ptr[4] = '7';
		ptr[5] = '4';
		ptr[6] = '8';
		ptr[7] = '3';
		ptr[8] = '6';
		ptr[9] = '4';
		ptr[10] = '8';
		ptr[11] = '\0';
		return (ptr);
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*ptr;

	count = bit_count(n);
	ptr = malloc_itoa(n, count);
	if (n == 0 || n == -2147483648)
	{
		ptr = exception(ptr, n);
		return (ptr);
	}
	if (n < 0)
	{
		ptr[0] = '-';
		n = -n;
		count = count + 1;
	}
	ptr[count--] = '\0';
	while (n > 0)
	{
		ptr[count--] = n % 10 + '0';
		n = n / 10;
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