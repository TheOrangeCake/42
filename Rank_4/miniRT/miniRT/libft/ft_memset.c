/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:13:40 by maw               #+#    #+#             */
/*   Updated: 2024/10/11 14:56:47 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*str;

	str = b;
	while (len > 0)
	{
		*str = (unsigned char)c;
		str++;
		len--;
	}
	return (b);
}

/*
 Cette fonction permet de remplir une zone mémoire, identifiée par son
 adresse et sa taille, avec une valeur précise. 
int main()
{
	char numero[] = {99, 88, 77, 55, 44};
	size_t size = 5 * sizeof(char);

	ft_memset(numero, 22, size);
	int i = 0;
	while (i < 5)
	{
		printf("[%d]", numero[i]);
		i++;
	}
	printf("\n");
	return (0);

}
*/