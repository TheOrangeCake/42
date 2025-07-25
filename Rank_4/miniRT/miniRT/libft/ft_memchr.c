/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:44:44 by maw               #+#    #+#             */
/*   Updated: 2024/10/11 12:40:54 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *mb, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)mb)[i] == (unsigned char)c)
			return ((unsigned char *)mb + i);
		i++;
	}
	return (NULL);
}

/*
Recherche la première occurence dune valeur typée int, mais
interprétée en tant que char, dans un bloc de mémoire.
Comme on traite un bloc de mémoire et non pas une chaîne de caractères
AZT (à zéro terminal), nous devons aussi spécifier à la fonction la taille
du bloc de mémoire dans lequel réaliser la recherche. 
int main()
{
	int data[] = {10, 20, 30, 40, 50};
	size_t size = 5 * sizeof(int);
	int *found = ft_memchr(data, 28, size);

	if (found != NULL)
		printf("%d", *found);
	else
		printf("not found");
	return (0);
}
*/