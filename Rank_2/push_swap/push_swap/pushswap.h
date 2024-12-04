/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:00:10 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/04 14:27:40 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H
# include "libft.h"

typedef struct s_pile
{
	int		number;
	int		index;
	void	*next;
}	t_pile;

int	ft_strcmp(char *s1, char *s2);
t_pile	*ft_lstnew(char *content);

#endif
