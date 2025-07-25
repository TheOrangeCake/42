/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:21:37 by maw               #+#    #+#             */
/*   Updated: 2025/06/08 20:15:26 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	resultat;

	resultat = 0;
	signe = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		signe *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		resultat *= 10;
		resultat = (str[i] - '0') + resultat;
		i++;
	}
	resultat *= signe;
	return (resultat);
}

// #include <stdlib.h>
// #include <stdio.h>
// int main()
// {
// const char nombre[] = "  ++46";

// printf("%d\n", ft_atoi(nombre));
// printf("%d\n", atoi(nombre));

// return (0);
// }