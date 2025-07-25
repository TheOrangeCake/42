/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:00:03 by maw               #+#    #+#             */
/*   Updated: 2024/10/11 15:11:31 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char) c == '\0')
		return ((char *)str);
	return (NULL);
}

/*
Returns a pointer to the first occurrence
of character in the C string str.
The terminating null-character is considered
part of the C string.
Therefore, it can also be located in order
to retrieve a pointer to the end of a string.
int main (void)
{
	char str[] = "je ne suis pas dans les classements";
	printf("%d", ft_strchr(str, 's'));
	return (0);
}
*/