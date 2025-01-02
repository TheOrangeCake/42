/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:10:49 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/02 13:59:27 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	sort_2(t_pile **a)
{
	t_pile	*temp;

	temp = *a;
	temp = temp->next;
	if ((*a)->numb > temp->numb)
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
		ra(a);
	else if ((*a)->numb > b->numb && b->numb < c->numb && c->numb > (*a)->numb)
		sa(a);
}
