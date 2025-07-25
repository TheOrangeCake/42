/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:47:22 by maw               #+#    #+#             */
/*   Updated: 2024/10/10 17:20:53 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char			*trim;
	unsigned int	start;
	unsigned int	end;
	size_t			len;

	if ((!s1) || (!set))
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]) != NULL)
		end--;
	len = end - start;
	trim = ft_substr(s1, start, len);
	if (trim == NULL)
		return (NULL);
	return (trim);
}

/*
Alloue (avec malloc(3)) et retourne une copie de
la chaîne ’s1’, sans les caractères spécifiés
dans ’set’ au début et à la fin de la chaîne de
caractères
int main(void)
{
	printf("%s\n", ft_strtrim("je suis un dj", "j"));
	printf("%s\n", ft_strtrim("alalalalal", "a"));
	printf("%s\n", ft_strtrim("abced", ""));
	printf("%s\n", ft_strtrim("abced", NULL));
	printf("%s\n", ft_strtrim("", ""));
	return(0);
}
*/