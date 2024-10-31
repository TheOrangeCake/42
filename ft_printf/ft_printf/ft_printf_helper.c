/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:08:01 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/31 18:19:37 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*case_hexupper(int i, size_t *count)
{
	char			*table;
	unsigned int	j;

	j = i;
	table = malloc(sizeof(char) * 17);
	if (table == NULL)
		return (NULL);
	table = "0123456789ABCDEF";
	if (j > 15)
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
	char			*table;
	unsigned int	j;

	j = i;
	table = malloc(sizeof(char) * 17);
	if (table == NULL)
		return (NULL);
	table = "0123456789abcdef";
	if (j > 15)
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

char	*case_address(long i, size_t *count)
{
	char			*table;
	unsigned long	j;

	j = i;
	write(1, "0x", 2);
	(*count) += 2;
	table = malloc(sizeof(char) * 17);
	if (table == NULL)
		return (NULL);
	table = "0123456789abcdef";
	if (j > 15)
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

void	case_unsigned(unsigned int n, int fd, size_t *count)
{
	char			base;
	unsigned int	j;

	j = n;
	if (j > 9)
	{
		case_unsigned(j / 10, fd, count);
		case_unsigned(j % 10, fd, count);
	}
	else
	{
		base = j + '0';
		ft_putchar_fd(base, fd);
		(*count)++;
	}
}
