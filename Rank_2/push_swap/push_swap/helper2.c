/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:27:01 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/10 21:26:44 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	quicksort_b_next(t_pile **a, t_pile **b, int pivot, int size)
{
	int	count;
	int	i;

	count = 0;
	i = size;
	while (i > 0)
	{
		if ((*b)->numb > pivot)
		{
			pa(a, b);
			count++;
		}
		else
			rb(b);
		i--;
	}
	pivot = 0;
	while (pivot++ < size - count)
		rrb(b);
	quicksort_a(a, b, count);
	quicksort_b(a, b, size - count);
	while (count-- > 0)
		pb(a, b);
}

void	quicksort_a_next(t_pile **a, t_pile **b, int pivot, int size)
{
	int	count;
	int	i;

	count = 0;
	i = size;
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
	pivot = 0;
	while (pivot++ < size - count)
		rra(a);
	quicksort_a(a, b, size - count);
	quicksort_b(a, b, count);
	while (count-- > 0)
		pa(a, b);
}
