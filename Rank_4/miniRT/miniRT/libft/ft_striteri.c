/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:49:14 by maw               #+#    #+#             */
/*   Updated: 2024/10/10 18:42:42 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*
Applique la fonction ’f’ à chaque caractère de la chaîne de caractères
passée en argument pour créer une nouvelle chaîne de caractères (avec malloc(3))
résultant des applications successives de ’f’.
void f(unsigned int i, char *c)
{
	i = 8;
	*c = *c + 3;
}

int main()
{
	char alpha[] = "abc";
	ft_striteri(alpha, f);
	printf("%s\n", alpha);
	return (0);
}
*/
