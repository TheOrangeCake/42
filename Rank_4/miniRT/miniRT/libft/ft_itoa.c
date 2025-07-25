/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:41:16 by maw               #+#    #+#             */
/*   Updated: 2024/09/01 19:30:14 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	intlen(int nb)
{
	int	i;

	if (nb == -2147483648)
		return (11);
	i = 0;
	if (nb == 0)
	{
		return (1);
	}
	if (nb < 0)
	{
		i++;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int				i;
	char			*res;
	long int		num;

	num = n;
	i = intlen(n);
	res = malloc((i + 1) * sizeof(char));
	if (res == NULL)
		return (res);
	res[i] = '\0';
	if (n == 0)
		res[0] = '0';
	if (n < 0)
	{
		res[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		i--;
		res[i] = num % 10 + '0';
		num /= 10;
	}
	return (res);
}

// #include <stdio.h>

// int main()
// {
//     int nb = -2147483648;

//     printf("%s\n", ft_itoa(nb));
//     return (0);
// }