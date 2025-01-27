/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_insertion_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:29:33 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/27 21:42:08 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	find_small_big(t_pile **a, int *smaller, int *smallest, int size)
{
	t_pile	*temp;
	int		i;

	i = size;
	temp = (*a);
	while (i-- > 0)
	{
		if (*smallest > temp->numb)
			*smallest = temp->numb;
		temp = temp->next;
	}
	temp = (*a);
	i = size;
	while (i-- > 0)
	{
		if (*smaller > temp->numb && temp->numb != *smallest)
			*smaller = temp->numb;
		temp = temp->next;
	}
}

void	find_big_big(t_pile **b, int *bigger, int *biggest, int size)
{
	t_pile	*temp;
	int		i;

	i = size;
	temp = (*b);
	while (i-- > 0)
	{
		if (*biggest < temp->numb)
			*biggest = temp->numb;
		temp = temp->next;
	}
	temp = (*b);
	i = size;
	while (i-- > 0)
	{
		if (*bigger < temp->numb && temp->numb != *biggest)
			*bigger = temp->numb;
		temp = temp->next;
	}
}

void	insertion_b_push_back(t_pile **a, t_pile **b, int size)
{
		while (size-- > 0)
		pb(a, b);
}

void	insertion_a_push_back(t_pile **a, t_pile **b, int size)
{
		while (size-- > 0)
		pa(a, b);
}

int	insertion_sort_b_small(t_pile **a, t_pile **b, int size)
{
	int	biggest;
	int	bigger;
	int	count;
	int	rotate;
	int	i;

	if (size < 1)
		return (0);
	biggest = (*b)->numb;
	bigger = -2147483648;
	count = 0;
	rotate = 0;
	i = size;
	find_big_big(b, &bigger, &biggest, size);
	while (i-- > 0 /* && (*b)->numb != smallest */)
	{
		if ((*b)->numb == biggest && count++ < 2147483647)
		{
			pa(a, b);
			break ;
		}
		else if ((*b)->numb != biggest && rotate++ < 2147483647)
			rb(b, 0);
	}
	while (rotate-- > 0)
	{
		rrb(b);
		if ((*b)->numb == bigger && count++ < 2147483647)
			pa(a, b);
	}
	// insertion_sort_b_small(a, b, size - count);
	return (count + insertion_sort_b_small(a, b, size - count));
}

int	insertion_sort_a_small(t_pile **a, t_pile **b, int size)
{
	int	smallest;
	int	smaller;
	int	count;
	int	rotate;
	int	i;

	if (size < 1)
		return (0);
	smallest = (*a)->numb;
	smaller = 2147483647;
	count = 0;
	rotate = 0;
	i = size;
	find_small_big(a, &smaller, &smallest, size);
	while (i-- > 0 /* && (*b)->numb != smallest */)
	{
		if ((*a)->numb == smallest && count++ < 2147483647)
		{
			pb(a, b);
			break ;
		}
		else if ((*a)->numb != smallest && rotate++ < 2147483647)
			ra(a, 0);
	}
	while (rotate-- > 0)
	{
		rra(a);
		if ((*a)->numb == smaller && count++ < 2147483647)
			pb(a, b);
	}
	// insertion_sort_a_small(a, b, size - count);
	return (count + insertion_sort_a_small(a, b, size - count));
}
