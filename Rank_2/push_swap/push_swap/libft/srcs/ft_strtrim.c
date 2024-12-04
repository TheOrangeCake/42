/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:24:43 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/11 16:12:20 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static int	check(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*ptr;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	j = ft_strlen(s1);
	while (i < j && s1[i] && check(s1[i], set) == 1)
		i++;
	while (j > i && check(s1[j - 1], set) == 1)
		j--;
	if (j == 0)
		i = 0;
	ptr = malloc(j - i + 1);
	if (ptr == NULL)
		return (NULL);
	k = 0;
	while (i < j)
		ptr[k++] = s1[i++];
	ptr[k] = '\0';
	return (ptr);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char const	s1[] = "123sdgsd321";
// 	char const	set[] = "123";

// 	printf("result: %s\n", ft_strtrim(s1, set));
// 	return (0);
// }
