/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:06:43 by maw               #+#    #+#             */
/*   Updated: 2024/10/10 18:51:36 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		modulo;
	char	reste;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n >= 10)
	{
		modulo = n % 10;
		reste = modulo + '0';
		ft_putnbr_fd(n / 10, fd);
		write(fd, &reste, 1);
	}
	if (n < 10)
	{
		reste = n + '0';
		write(fd, &reste, 1);
	}
}

/*
int main()
{
	int number;

	number = -90;
	ft_putnbr_fd(number, 1);
	return(0);
}
*/