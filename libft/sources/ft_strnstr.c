/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:16:19 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/09 14:46:50 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	const char	*ptr;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		ptr = &big[i];
		j = 0;
		while (big[i + j] == little[j])
		{
			j++;
			if (little[j] == '\0' && (i + j) <= len)
				return ((char *)ptr);
		}
		i++;
	}
	return (NULL);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	new[] = "hello, world";
// 	char	new1[] = "world";
// 	size_t	newlen;
// 	// char	old[] = "hello, world";
// 	// char	old1[] = "ello";
// 	// size_t	oldlen;

// 	newlen = 12;
// 	// oldlen = 9;
// 	printf("Result new: %s\n", ft_strnstr(new, new1, newlen));
// 	// printf("Result old: %s\n", strnstr(old, old1, oldlen));
// 	return (0);
// }