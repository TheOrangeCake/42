/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:18:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/06 16:40:41 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	insertion_sort_pivot(int array[], int size)
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

int	find_pivot(t_pile **a, t_pile **b, int size)
{
	int		*array;
	t_pile	*temp;
	int		i;

	array = (int *)malloc(size * sizeof(int));
	if (array == NULL)
	{
		write(2, "Error\n", 6);
		lstclear(a);
		free(a);
		lstclear(b);
		free(b);
		exit(1);
	}
	temp = *a;
	i = 0;
	while (temp != NULL && i < size)
	{
		array[i] = temp->numb;
		temp = temp->next;
		i++;
	}
	i = insertion_sort_pivot(array, size);
	free(array);
	return (i);
}

void	quicksort_a(t_pile **a, t_pile **b, int size)
{
	int	pivot;

	if (size <= 1 || !(*a) || sorted_a(a) == 0)
		return ;
	else if (size == 3)
	{
		sort_three_big(a);
		return ;
	}
	else if (size == 2)
	{
		sort_two(a);
		return ;
	}
	pivot = find_pivot(a, b, size);
	quicksort_a_next(a, b, pivot, size);
}

void	quicksort_b(t_pile **a, t_pile **b, int size)
{
	int	pivot;

	if (size <= 1 || !(*b) || sorted_b(b) == 0)
		return ;
	else if (size == 3)
	{
		sort_three_reverse_big(b);
		return ;
	}
	else if (size == 2)
	{
		sort_two_reverse(b);
		return ;
	}
	pivot = find_pivot(b, a, size);
	quicksort_b_next(a, b, pivot, size);
}

void	partitioning(t_pile **a, t_pile **b, int size)
{
	int	pivot;
	int	count;
	int	i;

	pivot = find_pivot(a, b, size);
	count = 0;
	i = size;
	while (i-- > 0)
	{
		if ((*a)->numb < pivot && count++ < size)
			pb(a, b);
		else
		{
			if (check_a(a, pivot, size - count) == 1)
				ra(a);
			else
				break ;
		}
	}
	quicksort_a(a, b, size - count);
	quicksort_b(a, b, count);
	while ((*b) != NULL)
		pa(a, b);
}
