/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:24:18 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/18 17:09:03 by hoannguy         ###   ########.fr       */
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

void	selection_sort(t_pile **a, t_pile **b)
{
	int	smallest;
	
	while ((*a) != NULL)
	{
		smallest = (*a)->numb;
		find_small_big(a, &smallest);
		if ((*a)->numb == smallest)
			pb(a, b);
		else
			ra(a, 0);
	}
	while ((*b) != NULL)
		pa(a, b);
}
