/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_move1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:45:38 by hoannguy          #+#    #+#             */
/*   Updated: 2025/02/02 14:34:07 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	pb(t_pile **a, t_pile **b)
{
	t_pile	*temp;

	temp = *a;
	if ((*a) != NULL)
	{
		*a = (*a)->next;
		temp->next = *b;
		*b = temp;
	}
}

void	pa(t_pile **a, t_pile **b)
{
	t_pile	*temp;

	temp = *b;
	if ((*b) != NULL)
	{
		*b = (*b)->next;
		temp->next = *a;
		*a = temp;
	}
}

void	sa(t_pile **a)
{
	t_pile	*temp;

	temp = *a;
	if ((*a) != NULL)
	{
		if (temp->next != NULL)
		{
			temp = temp->next;
			(*a)->next = temp->next;
			temp->next = *a;
			*a = temp;
		}
	}
}

void	sb(t_pile **b)
{
	t_pile	*temp;

	temp = *b;
	if ((*b) != NULL)
	{
		if (temp->next != NULL)
		{
			temp = temp->next;
			(*b)->next = temp->next;
			temp->next = *b;
			*b = temp;
		}
	}
}

void	ra(t_pile **a)
{
	t_pile	*temp;
	t_pile	*temp2;

	temp = *a;
	temp2 = *a;
	if ((*a) != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = *a;
		temp2 = temp2->next;
		(*a)->next = NULL;
		*a = temp2;
	}
}
