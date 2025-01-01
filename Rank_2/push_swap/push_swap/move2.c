/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:10:04 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/01 22:14:31 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	rb(t_pile **b)
{
	t_pile	*temp;
	t_pile	*temp2;

	temp = *b;
	temp2 = *b;
	while (temp -> next != NULL)
		temp = temp -> next;
	temp -> next = *b;
	temp2 = temp2 -> next;
	(*b) -> next = NULL;
	*b = temp2;
	ft_printf("rb\n");
}