/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:59:53 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/27 22:59:44 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	input_check(char *av[])
{
	int	i;
	int	j;

	i = 1;
	while (av[i] != NULL)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if ((av[i][j] < '0' || av[i][j] > '9') && (av[i][j] != ' '
					&& av[i][j] != '-' && av[i][j] != '+'))
				return (1);
			j++;
		}
		j = i + 1;
		while (av[j] != NULL)
		{
			if (ft_strcmp(av[i], av[j++]) == 0)
				return (1);
		}
		i++;
	}
	if (input_check_helper(av) == 1 || check_0(av) == 1)
		return (1);
	return (0);
}

t_pile	**initiate_a(char *av[], t_pile **a)
{
	t_pile	*node;
	int		i;

	i = 1;
	while (av[i] != NULL)
	{
		node = lstnew(av[i]);
		if (node == NULL)
			return (lstclear(a), NULL);
		lstadd_back(a, node);
		i++;
	}
	return (a);
}

int	sorted_a(t_pile **a)
{
	t_pile	*temp;
	int		i;

	temp = *a;
	i = temp->numb;
	temp = temp->next;
	while (temp != NULL)
	{
		if (i > temp->numb)
			return (1);
		i = temp->numb;
		temp = temp->next;
	}
	return (0);
}

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
	// else if (numb <= 100)
	// 	selection_sort(a, b);
	else
		partitioning(a, b ,numb);
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
