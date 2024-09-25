/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:25:20 by hoannguy          #+#    #+#             */
/*   Updated: 2024/09/20 15:31:14 by hoannguy         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int	result;

	result = nb;
	if (nb < 0)
		return (0);
	else if (nb == 0 || nb == 1)
		return (1);
	while (nb > 1)
	{
		result = result * (nb - 1);
		nb--;
	}
	return (result);
}

#include <stdio.h>

int	main(void)
{
	int	nb;

	nb = 10;
	printf("factorial of %d is %d\n", nb, ft_iterative_factorial(nb));
	return (0);
}