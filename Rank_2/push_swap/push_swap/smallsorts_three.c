/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smallsorts_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:05:58 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/10 18:05:24 by hoannguy         ###   ########.fr       */
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

void	find_small_big(t_pile **a, int *smaller, int *smallest)
{
	t_pile	*temp;
	int		i;

	temp = (*a);
	i = 5;
	while (temp != NULL && i > 0)
	{
		if (*smallest > temp->numb)
			*smallest = temp->numb;
		temp = temp->next;
		i--;
	}
	temp = (*a);
	i = 5;
	while (temp != NULL)
	{
		if (*smaller > temp->numb && temp->numb != *smallest && i > 0)
			*smaller = temp->numb;
		temp = temp->next;
		i--;
	}
}

void	find_big_big(t_pile **b, int *bigger, int *biggest)
{
	t_pile	*temp;
	int		i;

	temp = (*b);
	i = 5;
	while (temp != NULL && i > 0)
	{
		if (*biggest < temp->numb)
			*biggest = temp->numb;
		temp = temp->next;
		i--;
	}
	temp = (*b);
	i = 5;
	while (temp != NULL)
	{
		if (*bigger < temp->numb && temp->numb != *biggest && i > 0)
			*bigger = temp->numb;
		temp = temp->next;
		i--;
	}
}

void	sort_five_big(t_pile **a, t_pile **b)
{
	int		smallest;
	int		smaller;
	int		i;

	smallest = (*a)->numb;
	smaller = 2147483647;
	find_small_big(a, &smaller, &smallest);
	i = 5;
	while ((*a) != NULL && i > 0)
	{
		if ((*a)->numb == smaller || (*a)->numb == smallest)
			pb(a, b);
		else
			ra(a);
		i--;
	}
	rra(a);
	rra(a);
	rra(a);
	sort_three_big(a);
	sort_two_reverse(b);
	pa(a, b);
	pa(a, b);
}
