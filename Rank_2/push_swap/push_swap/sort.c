/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:10:49 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/02 13:27:06 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	sort_2(t_pile **a)
{
	t_pile	*temp;

	temp = *a;
	temp = temp -> next;
	if ((*a)-> number > temp -> number)
		sa(a);
}

void	sort_3(t_pile **a)
{
	t_pile	*b;
	t_pile	*c;

	b = *a;
	b = b -> next;
	c = b;
	c = c -> next;
	if ((*a)->number < b->number && b->number > c->number
		&& c->number > (*a)->number)
	{
		rra(a);
		sa(a);
	}
}
