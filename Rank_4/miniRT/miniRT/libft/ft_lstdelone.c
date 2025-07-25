/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:11:44 by maw               #+#    #+#             */
/*   Updated: 2025/07/11 17:16:23 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

// void	ft_free_content(void *content)
// {
//     free(content);
// }

// int	main(void)
// {
//     t_list	*node = ft_lstnew(malloc(10));

//     ft_lstdelone(node, ft_free_content);
//     return (0);
// }
