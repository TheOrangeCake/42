/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smallsorts_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:05:58 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/10 22:47:22 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	sort_three_big_next(t_pile **a)
{
	t_pile	*b;
	t_pile	*c;

	b = (*a)->next;
	c = b->next;
	if ((*a)->numb < b->numb && b->numb > c->numb && c->numb < (*a)->numb)
	{
		ra(a);
		sa(a);
		rra(a);
		sa(a);
	}
	else if ((*a)->numb > b->numb && b->numb > c->numb)
	{
		sa(a);
		ra(a);
		sa(a);
		rra(a);
		sa(a);
	}
}

void	sort_three_big(t_pile **a)
{
	t_pile	*b;
	t_pile	*c;

	b = (*a)->next;
	c = b->next;
	if ((*a)->numb < b->numb && b->numb > c->numb && c->numb > (*a)->numb)
	{
		ra(a);
		sa(a);
		rra(a);
	}
	else if (((*a)->numb < b->numb && b->numb > c->numb && c->numb < (*a)->numb)
		|| ((*a)->numb > b->numb && b->numb > c->numb))
		sort_three_big_next(a);
	else if ((*a)->numb > b->numb && b->numb < c->numb && c->numb < (*a)->numb)
	{
		sa(a);
		ra(a);
		sa(a);
		rra(a);
	}
	else if ((*a)->numb > b->numb && b->numb < c->numb && c->numb > (*a)->numb)
		sa(a);
}
