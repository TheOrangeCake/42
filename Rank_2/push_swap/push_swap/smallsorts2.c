/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smallsorts2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 22:50:02 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/22 22:23:27 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	sort_two_reverse(t_pile **b)
{
	t_pile	*temp;

	temp = *b;
	temp = temp->next;
	if ((*b)->numb < temp->numb)
		sb(b);
}

void	sort_three_reverse(t_pile **a)
{
	t_pile	*b;
	t_pile	*c;

	b = (*a)->next;
	c = b->next;
	if ((*a)->numb < b->numb && b->numb > c->numb && c->numb > (*a)->numb)
		rb(a);
	else if ((*a)->numb < b->numb && b->numb > c->numb && c->numb < (*a)->numb)
		sb(a);
	else if ((*a)->numb < b->numb && b->numb < c->numb)
	{
		sb(a);
		rrb(a);
	}
	else if ((*a)->numb > b->numb && b->numb < c->numb && c->numb < (*a)->numb)
	{
		rrb(a);
		sb(a);
	}
	else if ((*a)->numb > b->numb && b->numb < c->numb && c->numb > (*a)->numb)
		rrb(a);
}

void	sort_three_reverse_big_next(t_pile **a)
{
	t_pile	*b;
	t_pile	*c;

	b = (*a)->next;
	c = b->next;
	if ((*a)->numb > b->numb && b->numb < c->numb && c->numb < (*a)->numb)
	{
		rb(a);
		sb(a);
		rrb(a);
	}
	else if ((*a)->numb > b->numb && b->numb < c->numb && c->numb > (*a)->numb)
	{
		rb(a);
		sb(a);
		rrb(a);
		sb(a);
	}
}

void	sort_three_reverse_big(t_pile **a)
{
	t_pile	*b;
	t_pile	*c;

	b = (*a)->next;
	c = b->next;
	if ((*a)->numb < b->numb && b->numb > c->numb && c->numb > (*a)->numb)
	{
		sb(a);
		rb(a);
		sb(a);
		rrb(a);
	}
	else if ((*a)->numb < b->numb && b->numb > c->numb && c->numb < (*a)->numb)
		sb(a);
	else if ((*a)->numb < b->numb && b->numb < c->numb)
	{
		sb(a);
		rb(a);
		sb(a);
		rrb(a);
		sb(a);
	}
	else if (((*a)->numb > b->numb && b->numb < c->numb && c->numb < (*a)->numb)
		|| ((*a)->numb > b->numb && b->numb < c->numb && c->numb > (*a)->numb))
		sort_three_reverse_big_next(a);
}
