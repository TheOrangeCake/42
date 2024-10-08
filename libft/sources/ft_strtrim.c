/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:24:43 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/08 10:24:43 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

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

char *ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*ptr;

	i = 0;
	j = ft_strlen(s1);
	while (s1[i] && check(s1[i], set) == 1)
		i++;
	while (check(s1[j - 1], set) == 1)
		j--;
	ptr = malloc(j - i + 1);
	if (ptr == NULL)
		return (NULL);
	k = 0;
	while (i < j)
		ptr[k++] = s1[i++];
	ptr[k] = '\0';
	return (ptr);
}

#include <stdio.h>

int	main(void)
{
	char const	s1[] = "1231987asdf123";
	char const	set[] = "123";

	printf("result: %s\n", ft_strtrim(s1, set));
	return (0);
}