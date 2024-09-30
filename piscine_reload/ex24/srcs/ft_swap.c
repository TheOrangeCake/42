/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:07:31 by hoannguy          #+#    #+#             */
/*   Updated: 2024/09/29 16:07:31 by hoannguy         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

// #include <stdio.h>

// int main(void)
// {
// 	int	a;
// 	int	b;
// 	int	*ptra;
// 	int	*ptrb;

// 	a = 1;
// 	b = 2;
// 	ptra = &a;
// 	ptrb = &b;
// 	ft_swap(ptra, ptrb);
// 	printf("a value is %d\nb value is %d\n", a, b);
// 	return (0);
// }