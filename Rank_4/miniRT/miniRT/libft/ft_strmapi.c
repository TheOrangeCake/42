/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:22:44 by maw               #+#    #+#             */
/*   Updated: 2024/10/10 18:14:49 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (str == NULL)
		return (str);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
Applique la fonction ’f’ à chaque caractère de la chaîne de caractères
passée en argument pour créer une nouvelle chaîne de caractères (avec malloc(3))
résultant des applications successives de ’f’.
char f(unsigned int i, char c)
{
	char p;

	p = c + 3;
	return(p);
}

int main()
{
	char alpha[] = "abc";
	printf("%s\n", ft_strmapi(alpha, *f));
	return (0);
}
*/