/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:19:42 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/12 20:19:42 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	text[] = "Hello";
// 	t_list	*test;
// 	t_list	*temp;

// 	test = ft_lstnew(text);
// 	while (test)
// 	{
// 		printf("First: %s\n", (char *)test->content);
// 		test = test->next;
// 	}
// 	while (test)
// 	{
// 		temp = test->next;
// 		free(test);
// 		test = temp;
// 	}
// 	return (0);
// }
