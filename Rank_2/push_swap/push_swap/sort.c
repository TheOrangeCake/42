/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 23:10:49 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/01 23:36:17 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	sort_2(t_pile **a)
{
	t_pile	*temp;

	temp = *a;
	temp = temp -> next;
	if ((*a) -> number > temp -> number)
		sa(a);
}

void	sort_3(t_pile **a)
{
	t_pile	*temp;
	t_pile	*temp1;

	temp = *a;
	temp = temp -> next;
	temp2 = temp;
	temp2 = temp2 -> next;
}
