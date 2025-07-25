/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:52:06 by maw               #+#    #+#             */
/*   Updated: 2024/10/10 16:33:53 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if ((c >= 'A' && c <= 'Z'))
		c += 32;
	return (c);
}

/*
The character is stored in integer form in C programming.
When a character is passed as an argument, corresponding ASCII
value (integer) of the character is passed instead of that
character itself.

int main(void)
{
    char 	c;
	char	result;

    c = 'M';
    result = ft_tolower(c);
    printf("ft_tolower(%c) = %c\n", c, result);

    c = 'm';
    result = ft_tolower(c);
    printf("ft_tolower(%c) = %c\n", c, result);

    c = '+';
    result = ft_tolower(c);
    printf("ft_tolower(%c) = %c\n", c, result);

    return (0);
}
*/