/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigsorts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:18:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/02 22:29:48 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	sort_2_reverse(t_pile **b)
{
	t_pile	*temp;

	temp = *b;
	temp = temp->next;
	if ((*b)->numb < temp->numb)
		sb(b);
}

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

int	find_pivot(t_pile **a, int size)
{
	t_pile	*temp;
	int		i;
	
	temp = *a;
	i = 0;
	while (i < size/2)
	{
		temp = temp->next;
		i++;
	}
	return (temp->numb);
}

void	sort_all(t_pile **a, t_pile **b, int size)
{
	int	pivot;
	int	count;
	int	i;

	pivot = find_pivot(a, size);
	ft_printf("pivot: %d\n", pivot);
	ft_printf("size: %d\n", size);
	count = 0;
	i = size;
	if (size == 2)
	{
		sort_2_reverse(b);
		return;
	}
	else if (size == 3)
	{
		sort_3_reverse(b);
		return;
	}
	while (i > 0)
	{
		if ((*a)->numb < pivot)
		{
			pb(a, b);
			count++;
		}
		else
			ra(a);
		i--;
	}
	sort_all(a, b, size - count);
	sort_all(b, a, count);
	while (count > 0)
	{
		pa(a, b);
		count--;
	}
}
