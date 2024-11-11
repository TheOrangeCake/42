/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_alphabet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:55:11 by hoannguy          #+#    #+#             */
/*   Updated: 2024/09/29 15:56:19 by hoannguy         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_alphabet(void)
{
	int	a;

	a = 'a';
	while (a >= 'a' && a <= 'z')
	{
		write(1, &a, 1);
		a++;
	}
}

// int	main(void)
// {
// 	ft_print_alphabet();
// 	return (0);
// }