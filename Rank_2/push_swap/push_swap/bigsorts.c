/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigsorts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:18:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/02 15:36:46 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	sort_3_reverse(t_pile **a)
{
	t_pile	*b;
	t_pile	*c;

	b = *a;
	b = b -> next;
	c = b;
	c = c -> next;
	if ((*a)->numb < b->numb && b->numb > c->numb && c->numb > (*a)->numb)
		ra(a);
	else if ((*a)->numb < b->numb && b->numb > c->numb && c->numb < (*a)->numb)
		sa(a);
	else if ((*a)->numb < b->numb && b->numb < c->numb)
	{
		sa(a);
		rra(a);
	}
	else if ((*a)->numb > b->numb && b->numb < c->numb && c->numb < (*a)->numb)
	{
		rra(a);
		sa(a);
	}
	else if ((*a)->numb > b->numb && b->numb < c->numb && c->numb > (*a)->numb)
		rra(a);
}

void	sort_all(t_pile **a, t_pile **b, int numb)
{
	
}