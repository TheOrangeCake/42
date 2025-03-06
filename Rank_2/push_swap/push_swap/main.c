/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:59:53 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/06 07:35:53 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

t_pile	**push_swap(t_pile **a, int numb)
{
	t_pile	**b;

	b = malloc(sizeof(t_pile *));
	if (b == NULL)
		return (lstclear(a), NULL);
	*b = NULL;
	if (numb == 1)
		return (lstclear(b), free(b), a);
	if (sorted_a(a) == 0)
		return (lstclear(b), free(b), a);
	if (numb == 2)
		sort_two(a);
	else if (numb == 3)
		sort_three(a);
	else if (numb == 4)
		sort_four(a, b);
	else if (numb == 5)
		sort_five(a, b);
	else
		partitioning(a, b, numb);
	return (lstclear(b), free(b), a);
}

int	main(int ac, char *av[])
{
	t_pile	**a;

	a = malloc(sizeof(t_pile *));
	if (a == NULL)
		return (write(2, "Error\n", 6), 0);
	*a = NULL;
	if (ac > 1)
	{
		if (input_check(av) == 1)
			return (free(a), write(2, "Error\n", 6), 0);
		else
			a = initiate_a(av, a);
		if (a == NULL)
			return (free(a), write(2, "Error\n", 6), 0);
		a = push_swap(a, ac - 1);
		if (a == NULL)
			return (free(a), write(2, "Error\n", 6), 0);
	}
	else if (ac == 1)
		write(2, "Error\n", 6);
	return (lstclear(a), free(a), 0);
}

	// t_pile	*head2;
	// head2 = *a;
	// while (head2 != NULL)
	// {
	// 	ft_printf("a:%d\n", head2->numb);
	// 	head2 = head2 -> next;
	// }
	// head2 = *b;
	// while (head2 != NULL)
	// {
	// 	ft_printf("b:%d\n", head2 -> numb);
	// 	head2 = head2 -> next;
	// }
