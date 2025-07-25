/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:20:39 by maw               #+#    #+#             */
/*   Updated: 2024/10/11 13:06:08 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*call;

	call = malloc(count * size);
	if (call == NULL)
		return (NULL);
	ft_memset(call, 0, count * size);
	return (call);
}

/*
Cette fonction alloue un bloc de mémoire en initialisant tous ces octets à
la valeur 0. Bien que relativement proche de la fonction malloc, deux aspects
les différencient :

Linitialisation : calloc met tous les octets du bloc à la valeur 0 alors que
malloc ne modifie pas la zone de mémoire.
Les paramètres dappels : calloc requière deux paramètres (le nombre d'éléments
consécutifs à allouer et la taille dun élément) alors que malloc attend la taille
totale du bloc à allouer.
*/