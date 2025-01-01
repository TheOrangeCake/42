/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:00:27 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/01 22:32:55 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	pb(t_pile **a, t_pile **b)
{
	t_pile	*temp;

	temp = *a;
	*a = (*a) -> next;
	temp -> next = *b;
	*b = temp;
	ft_printf("pb\n");
}

void	pa(t_pile **a, t_pile **b)
{
	t_pile	*temp;

	temp = *b;
	*b = (*b) -> next;
	temp -> next = *a;
	*a = temp;
	ft_printf("pa\n");
}

void	sa(t_pile **a)
{
	t_pile	*temp;

	temp = *a;
	temp = temp -> next;
	(*a) -> next = temp -> next;
	temp -> next = *a;
	*a = temp;
	ft_printf("sa\n");
}

void	sb(t_pile **b)
{
	t_pile	*temp;

	temp = *b;
	temp = temp -> next;
	(*b) -> next = temp -> next;
	temp -> next = *b;
	*b = temp;
	ft_printf("sb\n");
}

void	ra(t_pile **a)
{
	t_pile	*temp;
	t_pile	*temp2;

	temp = *a;
	temp2 = *a;
	while (temp -> next != NULL)
		temp = temp -> next;
	temp -> next = *a;
	temp2 = temp2 -> next;
	(*a) -> next = NULL;
	*a = temp2;
	ft_printf("ra\n");
}
