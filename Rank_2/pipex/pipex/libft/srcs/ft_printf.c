/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:54:19 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/13 20:50:45 by hoannguy         ###   ########.fr       */
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

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

void	exception(int n, int fd, size_t *count)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		*count += 11;
	}
}

void	case_integer(int n, int fd, size_t *count)
{
	char	base;

	if (n == -2147483648)
		exception(n, fd, count);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		(*count)++;
		n = -n;
		case_integer(n, fd, count);
	}
	else
	{
		if (n > 9)
		{
			case_integer(n / 10, fd, count);
			case_integer(n % 10, fd, count);
		}
		else
		{
			base = n + '0';
			ft_putchar_fd(base, fd);
			(*count)++;
		}
	}
}

void	case_string(char *s, size_t *count)
{
	if (s == NULL)
	{
		write(1, "(null)", 6);
		*count += 6;
	}
	else
	{
		ft_putstr_fd(s, 1);
		*count += ft_strlen(s);
	}
}

void	specifier(char c, va_list list, size_t *count)
{
	if (c == '%')
	{
		ft_putchar_fd('%', 1);
		(*count)++;
	}
	if (c == 'c')
	{
		ft_putchar_fd(va_arg(list, int), 1);
		(*count)++;
	}
	if (c == 's')
		case_string(va_arg(list, char *), count);
	if (c == 'd' || c == 'i')
		case_integer(va_arg(list, int), 1, count);
	if (c == 'u')
		case_unsigned(va_arg(list, int), 1, count);
	if (c == 'x')
		case_hexlower(va_arg(list, unsigned int), count);
	if (c == 'X')
		case_hexupper(va_arg(list, unsigned int), count);
	if (c == 'p')
		case_address((unsigned long)va_arg(list, void *), count);
}

int	ft_printf(const char *format, ...)
{
	va_list	list;
	size_t	count;
	size_t	*ptr;
	size_t	i;

	va_start(list, format);
	i = 0;
	ptr = &count;
	*ptr = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			specifier(format[i], list, ptr);
			i++;
		}
		else
		{
			ft_putchar_fd(format[i++], 1);
			(*ptr)++;
		}
	}
	va_end(list);
	return (count);
}

// #include <stdio.h>
// #include <limits.h>

// int	main(void)
// {
// 	char	*ptr;
// 	char	*ptr1;
// 	int	i;
// 	int	j;
// 	char	c;
// 	char	d;
// 	int		a;
// 	int		b;

// 	ptr = malloc(sizeof(char) * 12 + 1);
// 	ptr1 = malloc(sizeof(char) * 12 + 1);
// 	ptr = "hello, world";
// 	ptr1 = "hello, world";
// 	c = 'b';
// 	d = 'b';
// 	a = 10000;
// 	b = 10000;

// 	i = ft_printf("%x\n", LONG_MAX);
// 	printf("%i\n", i);
// 	j = printf("%x\n", LONG_MAX);
// 	printf("%i\n", j);
// 	return (0);
// }
