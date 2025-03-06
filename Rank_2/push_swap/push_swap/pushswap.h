/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:00:10 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/06 16:39:50 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H
# include "libft.h"

typedef struct s_pile
{
	long	numb;
	void	*next;
	int		flag;
}	t_pile;

int		ft_strcmp(char *s1, char *s2);
void	lstadd_back(t_pile **lst, t_pile *new);
t_pile	*lstnew(void *content);
void	lstclear(t_pile **lst);
int		input_check_helper(char *av[]);
int		check_0(char *av[]);
int		sorted_a(t_pile **a);
int		sorted_b(t_pile **a);
t_pile	**initiate_a(char *av[], t_pile **a);
int		input_check(char *av[]);

void	pb(t_pile **a, t_pile **b);
void	pa(t_pile **a, t_pile **b);
void	sa(t_pile **a);
void	sb(t_pile **b);
void	ss(t_pile **a, t_pile **b);
void	ra(t_pile **a);
void	rb(t_pile **b);
void	rra(t_pile **a);
void	rrb(t_pile **b);

void	sort_two(t_pile **a);
void	sort_three(t_pile **a);
void	sort_four(t_pile **a, t_pile **b);
void	sort_five(t_pile **a, t_pile **b);
void	sort_two_reverse(t_pile **b);
void	sort_three_reverse(t_pile **a);
void	sort_three_big(t_pile **a);
void	sort_three_reverse_big(t_pile **a);
void	partitioning(t_pile **a, t_pile **b, int numb);
int		check_a(t_pile **a, int pivot, int size);
void	quicksort_b(t_pile **a, t_pile **b, int size);
void	quicksort_b_next(t_pile **a, t_pile **b, int pivot, int size);
void	quicksort_a(t_pile **a, t_pile **b, int size);
void	quicksort_a_next(t_pile **a, t_pile **b, int pivot, int size);

int		ft_strcmp_checker(char *s1, char *s2);

#endif
