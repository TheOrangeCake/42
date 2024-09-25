/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:07:49 by hoannguy          #+#    #+#             */
/*   Updated: 2024/09/20 14:36:57 by hoannguy         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

void ft_ft(int *nbr)
{
	*nbr = 42;
}

#include <stdio.h>

int main(void)
{
	int	a;
	int	*ptr;

	a = 90;
	ptr = &a;
	ft_ft(ptr);
	printf("The number is %d\n", a);
	return (0);
}