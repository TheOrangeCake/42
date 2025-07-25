/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:45:19 by maw               #+#    #+#             */
/*   Updated: 2024/10/31 18:04:47 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nod;

	nod = malloc(sizeof(t_list));
	if (nod == NULL)
		return (NULL);
	nod->content = content;
	nod->next = NULL;
	return (nod);
}

// int main()
// {
// 	char *str = "Kevin is in the Kitchen";
// 	t_list *ptr;

// 	ptr = ft_lstnew(str);
// 	printf("%s\n", (char *)ptr->content);
// 	return (0);
// }
