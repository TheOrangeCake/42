/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:43:49 by maw               #+#    #+#             */
/*   Updated: 2024/10/11 15:11:48 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (((char *)dest) < ((char *)src))
	{
		while (i < len)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	else
	{
		while (len > 0)
		{
			len--;
			((char *)dest)[len] = ((char *)src)[len];
		}
	}
	return (dest);
}

// Cette fonction permet de copier un bloc de mémoire
// spécifié par le paramètre source
// dans un nouvel emplacement désigné par le paramètre
// destination. On peut donc dire que
// cette fonction est proche de la fonction memcpy.
// Néanmoins, la différence réside dans
// le fait que la fonction memmove accepte que les deux
// zones de mémoire puissent se chevaucher.
// En cas de chevauchement, la copie se passe comme si
// les octets de la zone source étaient
// dabord copiés dans une zone temporaire, qui ne chevauche
// aucune des deux zones pointées
// par source et destination, et les octets sont ensuite
// copiés de la zone temporaire vers la zone
// de destination.

// int main()
// {
// 	int data[] = {20, 30, 40, 50, 60, 70, 80, 90, 100, 0};

// 	int i = 0;
// 	while (i < 10)
// 	{
// 		printf("[%d]", data[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	void *source = (void *) data;
// 	void *dest = (void *)(data + 1);
// 	size_t size = 9 * sizeof(int);
// 	ft_memmove(dest, source, size);
// 	data[0] = 10;
// 	i = 0;
// 	while (i < 10)
// 	{
// 		printf("[%d]", data[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	return (0);

// }
