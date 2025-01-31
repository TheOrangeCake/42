/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:44:25 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/31 22:56:34 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

t_pile	**do_move(t_pile **a, t_pile **b, char *line)
{
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (line != NULL && ft_strcmp_checker(line, "sa\n") == 0)
			sa(a);
		else if (line != NULL && ft_strcmp_checker(line, "sb\n") == 0)
			sb(b);
		else if (line != NULL && ft_strcmp_checker(line, "ss\n") == 0)
			ss(a, b);
		else if (line != NULL && ft_strcmp_checker(line, "pa\n") == 0)
			pa(a, b);
		else if (line != NULL && ft_strcmp_checker(line, "pb\n") == 0)
			pb(a, b);
		else if (line != NULL && ft_strcmp_checker(line, "ra\n") == 0)
			ra(a);
		else if (line != NULL && ft_strcmp_checker(line, "rb\n") == 0)
			rb(b);
		else if (line != NULL && ft_strcmp_checker(line, "rr\n") == 0)
		{
			ra(a);
			rb(b);
		}
		else if (line != NULL && ft_strcmp_checker(line, "rra\n") == 0)
			rra(a);
		else if (line != NULL && ft_strcmp_checker(line, "rrb\n") == 0)
			rrb(b);
		else if (line != NULL && ft_strcmp_checker(line, "rrr\n") == 0)
		{
			rra(a);
			rrb(b);
		}
		else
			return (write(2, "Error\n", 6), a);
	}
}

t_pile	**checker(t_pile **a)
{
	t_pile	**b;
	char	*line;

	b = malloc(sizeof(t_pile *));
	if (b == NULL)
		return (lstclear(a), NULL);
	*b = NULL;
	do_move(a, b, line);
	
	t_pile	*head2;
	head2 = *a;
	while (head2 != NULL)
	{
		ft_printf("a:%d\n", head2->numb);
		head2 = head2 -> next;
	}
	head2 = *b;
	while (head2 != NULL)
	{
		ft_printf("b:%d\n", head2 -> numb);
		head2 = head2 -> next;
	}
	
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
		a = checker(a);
		if (a == NULL)
			return (free(a), write(2, "Error\n", 6), 0);
	}
	else if (ac == 1)
		write(2, "Error\n", 6);
	return (lstclear(a), free(a), 0);
}
