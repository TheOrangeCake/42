/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:40:22 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/11 10:50:58 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// size_t	ft_strlcat(char *dst, const char *src, size_t size)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	dst_length;
// 	size_t	src_length;

// 	src_length = ft_strlen(src);
// 	dst_length = ft_strlen(dst);
// 	j = dst_length;
// 	i = 0;
// 	if (dst_length < size - 1 && size > 0)
// 	{
// 		while (src[i] && dst_length + i <= size)
// 		{
// 			dst[j] = src[i];
// 			j++;
// 			i++;
// 		}
// 		dst[j] = '\0';
// 	}
// 	return (dst_length + src_length);
// }

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	a;
	size_t	b;

	i = 0;
	j = 0;
	a = ft_strlen(dst);
	b = ft_strlen(src);
	if (size <= a)
		return (b + size);
	else
	{
		while (dst[i])
			i++;
		while (src[j] && (a + j) < size - 1)
		{
			dst[i++] = src[j++];
		}
		dst[i] = '\0';
	}
	return (a + b);
}
