/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:11:00 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/08 14:11:00 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>

// static size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// char **ft_split(char const *s, char c)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	s_len;
// 	char	**tab;
// 	char	*dup;

// 	i = 0;
// 	j = 1;
// 	s_len = ft_strlen(s);
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 			j++;
// 		i++;
// 	}
// 	if (s[i - 1] == c)
// 		j = j - 1;
// 	tab = malloc(sizeof(char *) * (j + 1));
// 	if (tab == NULL)
// 		return (NULL);
// 	dup = malloc(s_len + j + 1);
// 	if (dup == NULL)
// 	{
// 		free(tab);
// 		return (NULL);
// 	}
// 	i = 0;
// 	j = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 		{
// 			dup[j++] = s[i++];
// 			dup[j++] = '\0';
// 		}
// 		else
// 			dup[j++] = s[i++];
// 	}
// 	if (dup[j] != '\0')
// 		dup[j] = '\0';
// 	i = 0;
// 	j = 0;
// 	tab[i++] = &dup[j++];
// 	while (j < s_len)
// 	{
// 		if (dup[j] == '\0')
// 		{
// 			j++;
// 			tab[i++] = &dup[j];
// 		}
// 		j++;
// 	}
// 	tab[i] = '\0';
// 	return (tab);
// }

#include <stdio.h>

int	main(void)
{
	char	test[] = "abababababaaabaaabaaaabaa";
	char	split = 'b';
	int		a;
	char	**result;

	a = 0;
	result = ft_split(test, split);
	while (result[a])
	{
		printf("%s\n", result[a]);
		a++;
	}
	return (0);
}

