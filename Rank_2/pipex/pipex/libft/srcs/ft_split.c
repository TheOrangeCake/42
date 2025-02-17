/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:11:00 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/14 13:05:07 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlen(char const *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strdup(char const *src)
// {
// 	size_t	i;
// 	char	*ptr;

// 	i = 0;
// 	ptr = malloc(ft_strlen(src) * sizeof(char) + 1);
// 	if (ptr == NULL)
// 		return (NULL);
// 	while (src[i])
// 	{
// 		ptr[i] = src[i];
// 		i++;
// 	}
// 	ptr[i] = '\0';
// 	return (ptr);
// }

static char	*compare(char *str, char c)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			str[i] = '\0';
		}
		i++;
	}
	return (str);
}

// count number of word for malloc big array
static size_t	word_count(char *str, size_t len)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0')
			i++;
		i++;
	}
	return (count);
}

static char	**ft_splitting(char const *s, char *newstr, char **tab)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(s))
	{
		if (newstr[i] != '\0')
		{
			tab[j++] = ft_strdup(&newstr[i]);
			if (tab[j - 1] == NULL)
			{
				while (j > 0)
					free(tab[--j]);
				free(tab);
				return (NULL);
			}
			while (newstr[i] != '\0')
				i++;
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	*newstr;

	newstr = ft_strdup(s);
	if (newstr == NULL)
		return (NULL);
	newstr = compare(newstr, c);
	tab = malloc((word_count(newstr, ft_strlen(s)) + 1) * sizeof(char *));
	if (tab == NULL)
	{
		free(newstr);
		return (NULL);
	}
	tab = ft_splitting(s, newstr, tab);
	free(newstr);
	return (tab);
}

// #include <stdio.h>

// int main()
// {
// 	int	i;
//     char str[] = "ababbaaab";
//     char sep = 'a';

// 	i = 0;
// 	char **result = ft_split(str, sep);
// 	printf("Original string: \"%s\"\n", str);
//     printf("Split strings:\n");
//     while (result[i])
//     {
//         printf("[%d]: \"%s\"\n", i, result[i]);
// 		i++;
//     }
// 	printf("[%d]: \"%s\"\n", i, result[i]);
//     return (0);
// }
