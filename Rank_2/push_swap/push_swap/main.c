/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:59:53 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/02 13:59:01 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	input_check(char *av[])
{
	int	i;
	int	j;
	int	k;

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
		k = i + 1;
		while (av[k] != NULL)
		{
			if (ft_strcmp(av[i], av[k]) == 0)
				return (1);
			k++;
		}
		i++;
	}
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

t_pile	**push_swap(t_pile **a, int numb)
{
	t_pile	**b;

	b = malloc(sizeof(t_pile *));
	if (b == NULL)
		return (lstclear(a), NULL);
	*b = NULL;
	if (numb == 3)
		sort_2(a);
	if (numb == 4)
		sort_3(a);
	
	t_pile	*head2;
	head2 = *a;
	while (head2 != NULL)
	{
		ft_printf("1:%d\n", head2->numb);
		head2 = head2 -> next;
	}
	// head2 = *a;
	// while (head2 != NULL)
	// {
	// 	ft_printf("a:%d\n", head2 -> numb);
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
		a = push_swap(a, ac);
		if (a == NULL)
			return (free(a), write(2, "Error\n", 6), 0);
	}
	else if (ac == 1)
	{
		ft_printf("placeholder\n");
	}
	return (lstclear(a), free(a), 0);
}
