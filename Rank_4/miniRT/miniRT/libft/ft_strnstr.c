/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:17:06 by maw               #+#    #+#             */
/*   Updated: 2024/10/10 17:56:45 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	i;
	size_t	j;

	if (small[0] == '\0')
		return ((char *)big);
	i = 0;
	while ((big[i] && i < len))
	{
		j = 0;
		while ((small[j] == big[i + j] && (i + j) < len))
		{
			if (small[j + 1] == '\0')
				return (&((char *)big)[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

/*
The strnstr() function locates the first	occurrence of the  null-termi-
nated  string little in the string big, where not more than len charac-
ters are	searched.  Characters that appear after	a `\0'	character  are
not  searched.  Since the strnstr() function is a FreeBSD specific API,
it should only be used when portability is not a	concern.
If little is an empty string, big is returned; if little	occurs nowhere
in big, NULL is returned; otherwise a pointer to	the first character of
the first occurrence of little is returned.

int main()
{
	char big[] = "i was outside servin";
	char small[] = "outside";

	printf("%s\n", ft_strnstr(big, small, 30));
	printf("%s\n", ft_strnstr(big, small, 4));
	printf("%s\n", ft_strnstr(big, "", 10));
	printf("%s\n", ft_strnstr(big, "++__", 10));
	return (0);
}
*/