/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:54:19 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/24 21:54:19 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

static void	exception(int n, int fd, size_t *count)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		*count += 11;
	}
}

void	ft_putnbr_fd(int n, int fd, size_t *count)
{
	char	base;

	if (n == -2147483648)
		exception(n, fd, count);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		(*count)++;
		n = -n;
		ft_putnbr_fd(n, fd, count);
	}
	else
	{
		if (n > 9)
		{
			ft_putnbr_fd(n / 10, fd, count);
			ft_putnbr_fd(n % 10, fd, count);
		}
		else
		{
			base = n + '0';
			ft_putchar_fd(base, fd);
			(*count)++;
		}
	}
}

void	ft_putnbr_fd_unsigned(unsigned int n, int fd, size_t *count)
{
	char	base;

	if (n > 9)
	{
		ft_putnbr_fd_unsigned(n / 10, fd, count);
		ft_putnbr_fd_unsigned(n % 10, fd, count);
	}
	else
	{
		base = n + '0';
		ft_putchar_fd(base, fd);
		(*count)++;
	}
}

void	case_char(int c, size_t *count)
{
	ft_putchar_fd(c, 1);
	(*count)++;
}

void	case_string(char *s, size_t *count)
{
	ft_putstr_fd(s, 1);
	*count += ft_strlen(s);
}

void	case_interger(int i, size_t *count)
{
	ft_putnbr_fd(i, 1, count);
}

void	case_unsigned(int i, size_t *count)
{
	unsigned int	j;

	j = i;
	ft_putnbr_fd_unsigned(j, 1, count);
}

char	*case_hexupper(int i, size_t *count)
{
	char	*table;
	unsigned		j;

	j = i;
	table = malloc(sizeof(char) * 17);
	if (table == NULL)
		return (NULL);
	table = "0123456789ABCDEF";
	if (j > 16)
	{
		case_hexupper(j / 16, count);
		case_hexupper(j % 16, count);
	}
	else
	{
		ft_putchar_fd(table[j], 1);
		(*count)++;
	}
	return (table);
}

char	*case_hexlower(int i, size_t *count)
{
	char	*table;
	unsigned		j;

	j = i;
	table = malloc(sizeof(char) * 17);
	if (table == NULL)
		return (NULL);
	table = "0123456789abcdef";
	if (j > 16)
	{
		case_hexlower(j / 16, count);
		case_hexlower(j % 16, count);
	}
	else
	{
		ft_putchar_fd(table[j], 1);
		(*count)++;
	}
	return (table);
}
void	case_address(int i, size_t *count)
{
	write(1, "0x", 2);
	(*count) += 2;
	case_hexlower(i, count);
}

void	specifier(char c, va_list list, size_t *count)
{
	if (c == '%')
	{
		ft_putchar_fd('%', 1);
		(*count)++;
	}
	if (c == 'c')
		case_char(va_arg(list, int), count);
	if (c == 's')
		case_string(va_arg(list, char*), count);
	if (c == 'd' || c == 'i')
		case_interger(va_arg(list, int), count);
	if (c == 'u')
		case_unsigned(va_arg(list, int), count);
	if (c == 'x')
		case_hexlower(va_arg(list, int), count);
	if (c == 'X')
		case_hexupper(va_arg(list, int), count);
	if (c == 'p')
		case_address(va_arg(list, int), count);
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

#include <stdio.h>

int	main(void)
{
	char	*ptr;
	char	*ptr1;
	int	i;
	int	j;
	char	c;
	char	d;
	int		a;
	int		b;

	ptr = malloc(sizeof(char) * 12 + 1);
	ptr1 = malloc(sizeof(char) * 12 + 1);
	ptr = "hello, world";
	ptr1 = "hello, world";
	c = 'a';
	d = 'a';
	a = 1048576;
	b = 1048576;

	i = ft_printf("%p\n", ptr1);
	printf("%i\n", i);
	j = printf("%p\n", ptr1);
	printf("%i\n", j);
	return (0);
}