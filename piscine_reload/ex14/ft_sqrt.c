/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:21:01 by hoannguy          #+#    #+#             */
/*   Updated: 2024/09/20 16:22:39 by hoannguy         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int	a;

	a = 1;
	while (a * a < nb)
		a++;
	if (a * a == nb)
		return (a);
	else
		return (0);
}

#include <stdio.h>

int	main(void)
{
	int	a;
	int	result;

	a = 36111111;
	result = ft_sqrt(a);
	printf("square root of %d is %d\n", a, result);
	return (0);
}