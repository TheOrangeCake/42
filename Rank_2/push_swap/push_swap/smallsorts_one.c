/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smallsorts_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:10:49 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/12 19:51:49 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	sort_two(t_pile **a)
{
	t_pile	*temp;

	temp = *a;
	temp = temp->next;
	if ((*a)->numb > temp->numb)
		sa(a);
}

void	sort_three(t_pile **a)
{
	t_pile	*b;
	t_pile	*c;

	b = (*a)->next;
	c = b->next;
	if ((*a)->numb < b->numb && b->numb > c->numb && c->numb > (*a)->numb)
	{
		rra(a);
		sa(a);
	}
	else if ((*a)->numb < b->numb && b->numb > c->numb && c->numb < (*a)->numb)
		rra(a);
	else if ((*a)->numb > b->numb && b->numb > c->numb)
	{
		sa(a);
		rra(a);
	}
	else if ((*a)->numb > b->numb && b->numb < c->numb && c->numb < (*a)->numb)
		ra(a, 0);
	else if ((*a)->numb > b->numb && b->numb < c->numb && c->numb > (*a)->numb)
		sa(a);
}

void	find_small(t_pile **a, int *smaller, int *smallest)
{
	t_pile	*temp;

	temp = (*a);
	while (temp != NULL)
	{
		if (*smallest > temp->numb)
			*smallest = temp->numb;
		temp = temp->next;
	}
	temp = (*a);
	while (temp != NULL)
	{
		if (*smaller > temp->numb && temp->numb != *smallest)
			*smaller = temp->numb;
		temp = temp->next;
	}
}

void	sort_four(t_pile **a, t_pile **b)
{
	int		smallest;
	int		smaller;
	int		i;

	smallest = (*a)->numb;
	smaller = 2147483647;
	find_small(a, &smaller, &smallest);
	i = 5;
	while ((*a) != NULL && i > 0)
	{
		if ((*a)->numb == smallest)
			pb(a, b);
		else
			ra(a, 0);
		i--;
	}
	sort_three(a);
	pa(a, b);
}

void	sort_five(t_pile **a, t_pile **b)
{
	int	smallest;
	int	smaller;
	int	i;

	smallest = (*a)->numb;
	smaller = 2147483647;
	find_small(a, &smaller, &smallest);
	i = 5;
	while ((*a) != NULL && i > 0)
	{
		if ((*a)->numb == smaller || (*a)->numb == smallest)
			pb(a, b);
		else
			ra(a, 0);
		i--;
	}
	sort_three(a);
	sort_two_reverse(b);
	pa(a, b);
	pa(a, b);
}
