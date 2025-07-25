/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:46:07 by maw               #+#    #+#             */
/*   Updated: 2024/10/10 16:22:49 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ((c >= 'a' && c <= 'z'))
		c -= 32;
	return (c);
}

/*
Converts c to its uppercase equivalent if c is a lowercase letter 
and has an uppercase equivalent. If no such conversion is possible,
the value returned is c unchanged.
int	main(void)
{
	char c = 'A';
	char d = 'b';

	printf("%c\n", ft_toupper((int)c));
	printf("%c\n", ft_toupper((int)d));
	printf("%c\n", toupper((int)c));
	printf("%c\n", toupper((int)d));
	return (0);
}
*/