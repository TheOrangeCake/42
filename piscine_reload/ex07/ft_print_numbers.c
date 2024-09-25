/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:56:58 by hoannguy          #+#    #+#             */
/*   Updated: 2024/09/18 13:57:07 by hoannguy         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void ft_print_numbers(void)
{
	int	a;

	a = '0';
	while (a >= '0' && a <= '9')
	{
		write(1, &a, 1);
		a++;
	}
}

int	main(void)
{
	ft_print_numbers();
	return (0);
}