/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:00:10 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/01 15:11:45 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H
# include "libft.h"

typedef struct s_pile
{
	int		number;
	// int		index;
	void	*next;
}	t_pile;

int		ft_strcmp(char *s1, char *s2);
void	lstadd_back(t_pile **lst, t_pile *new);
t_pile	*lstnew(void *content);
void	lstclear(t_pile **lst);
void	pb(t_pile **a, t_pile **b);
void	pa(t_pile **a, t_pile **b);

#endif
