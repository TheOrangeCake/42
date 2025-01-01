/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:00:27 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/01 15:17:13 by hoannguy         ###   ########.fr       */
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

	// temp = *a;
	// *a = (*a) -> next;
	// temp -> next = *a;
	// *a = temp;
	ft_printf("sa\n");
}