/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:59:53 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/07 16:55:45 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	free_split(char **list)
{
	int	i;

	i = 0;
	while (list[i] != NULL)
	{
		free(list[i]);
		i++;
	}
	free(list);
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
	else
		partitioning(a, b, numb);
	return (lstclear(b), free(b), a);
}

t_pile	**run(t_pile **a, int ac, char **av)
{
	if (input_check(av) == 1)
		return (NULL);
	else
		a = initiate_a(av, a);
	if (a == NULL)
		return (NULL);
	a = push_swap(a, ac - 1);
	if (a == NULL)
		return (NULL);
	return (a);
}

char	**transform(char **av)
{
	int		i;
	int		j;
	int		count;
	char	**split;

	i = 0;
	count = 0;
	while (av[i] != NULL)
	{
		split = ft_split(av[i], ' ');
		if (split == NULL)
			return (NULL);
		j = 0;
		while (split[j++] != NULL)
			count++;
		free_split(split);
		i++;
	}
	split = transform_next(av, split, count);
	return (split);
}

int	main(int ac, char *av[])
{
	t_pile	**a;
	char	**split;

	a = malloc(sizeof(t_pile *));
	if (a == NULL)
		return (write(2, "Error\n", 6), 1);
	*a = NULL;
	if (ac > 1 && av[1] != NULL && av[1][0] != '\0')
	{
		split = transform(av);
		if (split == NULL || split[1] == NULL )
			return (free_split(split), write(2, "Error\n", 6), free(a), 1);
		ac = ac_count(split);
		if (run(a, ac, split) == NULL)
			return (free_split(split), free(a), write(2, "Error\n", 6), 1);
		free_split(split);
	}
	else if ((ac > 1 && av[1] != NULL) || (ac > 1 && av[1][0] != '\0'))
		return (write(2, "Error\n", 6), free(a), 1);
	else
		return (free(a), 1);
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
