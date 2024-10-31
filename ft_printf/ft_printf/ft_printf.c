/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:54:19 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/31 18:19:34 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
		case_integer('-', fd, count);
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
	ft_putstr_fd(s, 1);
	*count += ft_strlen(s);
}

// void	case_unsigned(unsigned int n, int fd, size_t *count)
// {
// 	char	base;
// 	unsigned int	j;

// 	j = n;
// 	if (j > 9)
// 	{
// 		case_unsigned(j / 10, fd, count);
// 		case_unsigned(j % 10, fd, count);
// 	}
// 	else
// 	{
// 		base = j + '0';
// 		ft_putchar_fd(base, fd);
// 		(*count)++;
// 	}
// }

// char	*case_hexupper(int i, size_t *count)
// {
// 	char	*table;
// 	unsigned		j;

// 	j = i;
// 	table = malloc(sizeof(char) * 17);
// 	if (table == NULL)
// 		return (NULL);
// 	table = "0123456789ABCDEF";
// 	if (j > 15)
// 	{
// 		case_hexupper(j / 16, count);
// 		case_hexupper(j % 16, count);
// 	}
// 	else
// 	{
// 		ft_putchar_fd(table[j], 1);
// 		(*count)++;
// 	}
// 	return (table);
// }

// char	*case_hexlower(int i, size_t *count)
// {
// 	char	*table;
// 	unsigned		j;

// 	j = i;
// 	table = malloc(sizeof(char) * 17);
// 	if (table == NULL)
// 		return (NULL);
// 	table = "0123456789abcdef";
// 	if (j > 15)
// 	{
// 		case_hexlower(j / 16, count);
// 		case_hexlower(j % 16, count);
// 	}
// 	else
// 	{
// 		ft_putchar_fd(table[j], 1);
// 		(*count)++;
// 	}
// 	return (table);
// }

// char	*case_address(long i, size_t *count)
// {
// 	char			*table;
// 	unsigned long	j;

// 	j = i;
// 	write(1, "0x", 2);
// 	(*count) += 2;
// 	table = malloc(sizeof(char) * 17);
// 	if (table == NULL)
// 		return (NULL);
// 	table = "0123456789abcdef";
// 	if (j > 15)
// 	{
// 		case_hexlower(j / 16, count);
// 		case_hexlower(j % 16, count);
// 	}
// 	else
// 	{
// 		ft_putchar_fd(table[j], 1);
// 		(*count)++;
// 	}
// 	return (table);
// }

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
		case_hexlower(va_arg(list, int), count);
	if (c == 'X')
		case_hexupper(va_arg(list, int), count);
	if (c == 'p')
		case_address(va_arg(list, long), count);
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
// 	a = 1;
// 	b = 1;

// 	i = ft_printf("test: %x\n%i\n%X\n%s\n%c\n%p\n%u\n", a, a, b, ptr, c, ptr1, a);
// 	printf("%i\n", i);
// 	j = printf("test: %x\n%i\n%X\n%s\n%c\n%p\n%u\n", a, a, b, ptr1, d, ptr1, b);
// 	printf("%i\n", j);
// 	return (0);
// }
