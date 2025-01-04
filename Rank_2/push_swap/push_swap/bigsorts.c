/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigsorts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:18:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/04 21:16:36 by hoannguy         ###   ########.fr       */
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

	b = *a;
	b = b -> next;
	c = b;
	c = c -> next;
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

// int	find_pivot(t_pile **a, int size)
// {
// 	t_pile	*temp;
// 	int		i;
	
// 	temp = *a;
// 	i = 1;
// 	while (i < size/2)
// 	{
// 		temp = temp->next;
// 		i++;
// 	}
// 	return (temp->numb);
// }

int	find_pivot(t_pile **a, int size)
{
	int		array[size];
	t_pile	*temp;
	int		i;

	temp = *a;
	while ((*temp) != NULL)
	{
		array[i] = temp->numb;
		temp = temp->next;
		i++;
	}
	return (bubble)
}

void	quicksort_a(t_pile **a, t_pile **b, int size)
{
	int	pivot;
	int	count;
	int	i;

	ft_printf("size a: %d\n", size);
	if (size <= 1 || !(*a))
        return;
	if (size == 3)
	{
		sort_three(a);
		return;
	}
	else if (size == 2)
	{
		sort_two(a);
		return;
	}
	pivot = find_pivot(a, size);
	count = 0;
	i = size;
	while (i > 0)
	{
		if ((*a)->numb <= pivot)
		{
			pb(a, b);
			count++;
		}
		else
			ra(a);
		i--;
	}
	quicksort_a(a, b, size - count);
	quicksort_b(a, b, count);
	while (count > 0)
	{
		pa(a, b);
		count--;
	}
}

void	quicksort_b(t_pile **a, t_pile **b, int size)
{
	int	pivot;
	int	count;
	int	i;

	ft_printf("size b: %d\n", size);
	if (size <= 1 || !(*b))
        return;
	if (size == 3)
	{
		sort_three_reverse(b);
		return;
	}
	else if (size == 2)
	{
		sort_two_reverse(b);
		return;
	}
	pivot = find_pivot(b, size);
	count = 0;
	i = size;
	while (i > 0)
	{
		if ((*b)->numb >= pivot)
		{
			pa(a, b);
			count++;
		}
		else
			rb(b);
		i--;
	}
	quicksort_a(a, b, count);
	quicksort_b(a, b, size - count);
	while (count > 0)
	{
		pb(a, b);
		count--;
	}
}

void	partitioning(t_pile **a, t_pile **b, int size)
{
	int	pivot;
	int	count;
	int	i;

	pivot = find_pivot(a, size);
	count = 0;
	i = size;
	while (i > 0)
	{
		if ((*a)->numb <= pivot)
		{
			pb(a, b);
			count++;
		}
		else
			ra(a);
		i--;
	}
	quicksort_a(a, b, size - count);
	quicksort_b(a, b, count);
	while (count > 0)
	{
		pa(a, b);
		count--;
	}
}
