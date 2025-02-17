/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 18:05:25 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/18 14:53:41 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

int	ft_atoi_hex(const char *ptr)
{
	int	i;
	int	nb;

	nb = 0;
	i = 0;
	while (ptr[i] && ((ptr[i] != '0'
				|| (ptr[i + 1] != 'x' && ptr[i + 1] != 'X'))))
		i++;
	if (ptr[i] == '0' && (ptr[i + 1] == 'x' || ptr[i + 1] == 'X'))
		i += 2;
	while ((ptr[i] >= '0' && ptr[i] <= '9')
		|| (ptr[i] >= 'a' && ptr[i] <= 'f')
		|| (ptr[i] >= 'A' && ptr[i] <= 'F'))
	{
		if (ptr[i] >= '0' && ptr[i] <= '9')
			nb = nb * 16 + (ptr[i] - '0');
		else if (ptr[i] >= 'a' && ptr[i] <= 'f')
			nb = nb * 16 + (ptr[i] - 'a' + 10);
		else if (ptr[i] >= 'A' && ptr[i] <= 'F')
			nb = nb * 16 + (ptr[i] - 'A' + 10);
		i++;
	}
	return (nb);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char	new[] = "0xffffff";

// 	printf("New: %d\n", ft_atoi_hex(new));
// 	return (0);
// }