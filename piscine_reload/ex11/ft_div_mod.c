/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:45:28 by hoannguy          #+#    #+#             */
/*   Updated: 2024/09/20 14:52:10 by hoannguy         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

void	ft_div_mod(int a, int b, int *div, int *mod)
{
	*div = a/b;
	*mod = a%b;
}

#include <stdio.h>

int	main(void)
{
	int	a;
	int	b;
	int	div;
	int	mod;
	int	*ptrdiv;
	int	*ptrmod;

	a = 9;
	b = 4;
	div = -1;
	mod = -2;
	ptrdiv = &div;
	ptrmod = &mod;
	printf("div is %d\nmod is %d\n", div, mod);
	ft_div_mod(a , b, ptrdiv, ptrmod);
	printf("new div is %d\nnew mod is %d\n", div, mod);
	return (0);
}