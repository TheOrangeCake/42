/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigsorts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:18:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/06 00:12:15 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	insertionSort(int array[], int size)
{
	int	i;
	int	j;
	int	number;

	i = 1;
	while (i < size)
	{
		number = array[i];
		j = i - 1;
		while (j >= 0 && array[j] > number)
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = number;
		i++;
	}
	if (size % 2 == 0)
		number = array[size / 2 - 1];
	else
		number = array[size / 2];
	return (number);
}

int	find_pivot(t_pile **a, int size)
{
	int		array[size];
	t_pile	*temp;
	int		i;

	temp = *a;
	i = 0;
	while (temp != NULL)
	{
		array[i] = temp->numb;
		temp = temp->next;
		i++;
	}
	return (insertionSort(array, size));
}

void	quicksort_a(t_pile **a, t_pile **b, int size)
{
	int	pivot;
	int	count;
	int	i;

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
	//quicksort_b(a, b, count);
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
	//quicksort_a(a, b, count);
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
	ft_printf("pivot: %d\n", pivot);
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
