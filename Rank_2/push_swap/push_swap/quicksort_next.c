/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_next.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:27:01 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/27 23:01:48 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	sorted_b(t_pile **a)
{
	t_pile	*temp;
	int		i;

	temp = *a;
	i = temp->numb;
	temp = temp->next;
	while (temp != NULL)
	{
		if (i < temp->numb)
			return (1);
		i = temp->numb;
		temp = temp->next;
	}
	return (0);
}

int	check_a(t_pile **a, int pivot, int size)
{
	t_pile	*temp;

	temp = *a;
	while (size-- > 0)
	{
		if (temp->numb < pivot)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	check_b(t_pile **a, int pivot, int size)
{
	t_pile	*temp;

	temp = *a;
	while (size-- > 0)
	{
		if (temp->numb > pivot)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	quicksort_a_next(t_pile **a, t_pile **b, int pivot, int size)
{
	int	count;
	int	i;
	int	rotate;

	count = 0;
	i = size;
	rotate = 0;
	while (i-- > 0)
	{
		if ((*a)->numb < pivot && count++ < size)
			pb(a, b);
		else
		{
			if (check_a(a, pivot, size - count) == 1 && rotate++ < size)
				ra(a);
			else
				break ;
		}
	}
	while (rotate-- > 0)
		rra(a);
	quicksort_a(a, b, size - count);
	quicksort_b(a, b, count);
	while (count-- > 0)
		pa(a, b);
}

void	quicksort_b_next(t_pile **a, t_pile **b, int pivot, int size)
{
	int	count;
	int	i;
	int	rotate;

	count = 0;
	i = size;
	rotate = 0;
	while (i-- > 0)
	{
		if ((*b)->numb > pivot && count++ < size)
			pa(a, b);
		else
		{
			if (check_b(b, pivot, size - count) == 1 && rotate++ < size)
				rb(b);
			else
				break ;
		}
	}
	while (rotate-- > 0)
		rrb(b);
	quicksort_a(a, b, count);
	quicksort_b(a, b, size - count);
	while (count-- > 0)
		pb(a, b);
}
