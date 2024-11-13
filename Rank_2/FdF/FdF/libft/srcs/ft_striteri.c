/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:42:21 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/09 14:53:24 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

// #include <stdio.h>

// void my_func(unsigned int i, char *c) {
//     *c = *c + i;
// }

// int main() {
//     char str[] = "123";
//     ft_striteri(str, my_func);
//     printf("%s\n", str);
//     return 0;
// }
