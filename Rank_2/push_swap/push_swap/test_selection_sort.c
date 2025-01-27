/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 21:18:03 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/27 21:41:08 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	find_small_big(t_pile **a, int *smallest)
{
	t_pile	*temp;

	if (a == NULL || *a == NULL)
		return ;
	temp = (*a);
	while (temp != NULL)
	{
		if (*smallest > temp->numb)
			*smallest = temp->numb;
		temp = temp->next;
	}
}

void	find_big_big(t_pile **a, int *biggest)
{
	t_pile	*temp;

	if (a == NULL || *a == NULL)
		return ;
	temp = (*a);
	while (temp != NULL)
	{
		if (*biggest < temp->numb)
			*biggest = temp->numb;
		temp = temp->next;
	}
}

int	direction(t_pile ** a, int *smallest, int *biggest, int size)
{
	int		pos1;
	int		pos2;
	int		count1;
	int		count2;
	t_pile	*temp;

	temp = (*a);
	pos1 = 0;
	pos2 = 0;
	while (temp->numb != *smallest && temp != NULL)
	{
		pos1++;
		temp = temp->next;
	}
	temp = (*a);
	while (temp->numb != *biggest && temp != NULL)
	{
		pos2++;
		temp = temp->next;
	}
	if (pos1 >= size/2)
		count1 = size - pos1;
	else
		count1 = pos1;
	if (pos2 >= size/2)
		count2 = size - pos2;
	else
	count2 = pos2;
	if (count1 >= count2)
	{
		if (pos2 >= size/2)
			return (1);
		else
			return (0);
	}
	else
	{
		if (pos1 >= size/2)
			return (1);
		else
			return (0);
	}
}

void	selection_sort(t_pile **a, t_pile **b, int size)
{
	int	smallest;
	int	biggest;
	t_pile	*head2;
	
	while ((*a) != NULL && size > 5)
	{
		biggest = -2147483648;
		smallest = 2147483647;
		find_big_big(a, &biggest);
		find_small_big(a, &smallest);
		if (direction(a, &smallest, &biggest, size) == 1)
		{
			while ((*a)->numb != smallest && (*a)->numb != biggest)
				rra(a);
		}
		else
		{
			while ((*a)->numb != smallest && (*a)->numb != biggest)
				ra(a);
		}
		pb(a, b);
		size--;
	}
	if (size == 5)
		sort_five(a, b);
	while ((*b) != NULL)
	{
		if ((*a)->numb < (*b)->numb)
		{
			pa(a, b);
			ra(a);
		}
		if ((*a)->numb > (*b)->numb)
			pa(a, b);
	}
}
