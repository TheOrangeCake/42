/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:44:44 by maw               #+#    #+#             */
/*   Updated: 2024/10/12 14:02:21 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	countwords(const char *str, char c)
{
	size_t	i;
	size_t	count;
	int		in;

	in = 0;
	i = 0;
	count = 0;
	if (!str)
		return (count);
	while (str[i])
	{
		if (str[i] != c && in == 0)
		{
			count++;
			in = 1;
		}
		else if (str[i] == c)
			in = 0;
		i++;
	}
	return (count);
}

void	freesplit(char **tab, size_t number)
{
	while (number > 0)
		free(tab[--number]);
	free(tab);
}

char	**writesplit(const char *s, char **split, char c, size_t num)
{
	size_t	start;
	size_t	i;

	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (i > start)
		{
			split[num] = ft_substr(s, start, i - start);
			if (split[num] == NULL)
			{
				freesplit(split, num);
				return (NULL);
			}
			num++;
		}
	}
	split[num] = NULL;
	return (split);
}

char	**ft_split(const char *s, char c)
{
	char	**split;
	size_t	num;

	split = malloc((countwords(s, c) + 1) * sizeof(char *));
	if (split == NULL || s == NULL)
		return (NULL);
	num = 0;
	split = writesplit(s, split, c, num);
	return (split);
}

// int main (void)
// {
// 	char mot[]= "hello!zzzzzzzz";
// 	// char set = ' ';
// 	char **tab;
// 	int i;

// 	tab = ft_split(mot, 'z');
// 	i = 0;
// 	while (tab[i])
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// 	return (0);
// }