/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:43:04 by maw               #+#    #+#             */
/*   Updated: 2024/10/10 17:00:22 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*sub;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = malloc((len + 1) * sizeof(char));
	if (sub == NULL)
		return (sub);
	i = 0;
	while (s[start] && i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}

/*
La fonction SUBSTR( ) renvoie des caractères de la valeur de la chaîne à 
partir de la position du caractère précisé par start. Le nombre de caractères
renvoyé est spécifié par la longueur.

int main(void)
{
	printf("%s\n", ft_substr("une bonne pate a crepe", 4, 10));
	printf("%s\n", ft_substr("", 4, 10));
	printf("%s\n", ft_substr("une bonne pate a pancakes", 0, -4));
	return (0);
}
*/