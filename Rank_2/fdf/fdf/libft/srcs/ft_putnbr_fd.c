/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:59:58 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/11 14:18:47 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_putchar_fd(char c, int fd)
// {
// 	write(fd, &c, 1);
// }

// void	ft_putstr_fd(char *s, int fd)
// {
// 	while (*s)
// 	{
// 		write(fd, s, 1);
// 		s++;
// 	}
// }

static void	exception(int n, int fd)
{
	if (n == 0)
		ft_putstr_fd("0", fd);
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	base;

	if (n == 0 || n == -2147483648)
	{
		exception(n, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
		ft_putnbr_fd(n, fd);
	}
	else
	{
		if (n > 9)
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putnbr_fd(n % 10, fd);
		}
		else
		{
			base = n + '0';
			ft_putchar_fd(base, fd);
		}
	}
}

// int	main()
// {
// 	ft_putnbr_fd(0, 1);
// 	write(1, "\n", 1);
// 	ft_putnbr_fd(42, 1);
// 	write(1, "\n", 1);
// 	ft_putnbr_fd(-42, 1);
// 	write(1, "\n", 1);
// 	ft_putnbr_fd(-2147483648, 1);
// 	write(1, "\n", 1);
// 	ft_putnbr_fd(2147483647, 1);
// 	write(1, "\n", 1);
// 	return (0);
// }