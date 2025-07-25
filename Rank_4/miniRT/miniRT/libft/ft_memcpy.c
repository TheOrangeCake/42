/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:41:32 by maw               #+#    #+#             */
/*   Updated: 2024/10/11 15:10:38 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (0);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

/*
Cette fonction permet de copier un bloc de mémoire
spécifié par le paramètre source,
et dont la taille est spécifiée via le paramètre size,
dans un nouvel emplacement désigné
par le paramètre destination. Il est bien entendu quil
est de votre responsabilité dallouer
suffisamment de mémoire pour le bloc de destination
afin quil puisse contenir toutes les données.
En cas de chevauchement des deux blocs de mémoire
(source et destination) le comportement
de la fonction memcpy nest pas garanti. Dans ce cas,
veuillez préférer lutilisation de la
fonction memmove.

int main()
{
	int numero[] = {18, 17, 23, 67, 45};
	int *copy = NULL;

	copy = malloc(5 * sizeof(int));
	ft_memcpy(copy, numero, 5 * sizeof(int));
	int i = 0;
	while (i < 5)
	{
		printf("[%d]", copy[i]);
		i++;
	}
	printf("\n");
	free (copy);
	return (0);
}
*/