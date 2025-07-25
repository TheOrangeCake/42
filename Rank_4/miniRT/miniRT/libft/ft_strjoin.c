/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:54:58 by maw               #+#    #+#             */
/*   Updated: 2024/10/10 18:25:36 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		lent;
	char	*join;

	j = 0;
	i = 0;
	lent = 0;
	lent += ft_strlen(s1) + ft_strlen(s2);
	join = malloc((lent + 1) * sizeof(char));
	if (join == NULL)
		return (join);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	return (join);
}

/*
Alloue (avec malloc(3)) et retourne une nouvelle chaîne,
résultat de la concaténation de s1 et s2.

int main()
{
	printf("%s\n" ,ft_strjoin("je ne m'en", " remet pas"));
	printf("%s\n" ,ft_strjoin("je ne m'en", ""));
	printf("%s\n" ,ft_strjoin("", "remet pas"));
	return(0);
}
*/