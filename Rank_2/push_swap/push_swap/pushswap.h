/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:00:10 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/02 13:56:27 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H
# include "libft.h"

typedef struct s_pile
{
	int		numb;
	// int		index;
	void	*next;
}	t_pile;

int		ft_strcmp(char *s1, char *s2);
void	lstadd_back(t_pile **lst, t_pile *new);
t_pile	*lstnew(void *content);
void	lstclear(t_pile **lst);
void	pb(t_pile **a, t_pile **b);
void	pa(t_pile **a, t_pile **b);
void	sa(t_pile **a);
void	sb(t_pile **b);
void	ra(t_pile **a);
void	rb(t_pile **b);
void	rra(t_pile **a);
void	rrb(t_pile **b);
void	sort_2(t_pile **a);
void	sort_3(t_pile **a);

#endif
