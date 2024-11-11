/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:08:01 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/01 11:50:51 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// size_t	ft_strlcpy(char *dst, const char *src, size_t size)
// {
// 	size_t	i;

// 	i = 0;
// 	if (size > 0)
// 	{
// 		while (src[i] && i < (size - 1))
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 		dst[i] = '\0';
// 	}
// 	while (src[i])
// 		i++;
// 	return (i);
// }

void	case_hexupper(unsigned int j, size_t *count)
{
	char			table[17];

	ft_strlcpy(table, "0123456789ABCDEF", 17);
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
}

void	case_hexlower(unsigned int j, size_t *count)
{
	char			table[17];

	ft_strlcpy(table, "0123456789abcdef", 17);
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
}

void	case_address_helper(unsigned long j, size_t *count)
{
	char			table[17];

	ft_strlcpy(table, "0123456789abcdef", 17);
	if (j > 15)
	{
		case_address_helper(j / 16, count);
		case_address_helper(j % 16, count);
	}
	else
	{
		ft_putchar_fd(table[j], 1);
		(*count)++;
	}
}

void	case_address(unsigned long j, size_t *count)
{
	char			table[17];

	ft_strlcpy(table, "0123456789abcdef", 17);
	write(1, "0x", 2);
	(*count) += 2;
	case_address_helper(j, count);
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
