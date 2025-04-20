/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:05:19 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/20 12:42:44 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	main(int ac, char **av, char **envp)
{
	t_token token1;
	t_token token2;
	t_token token3;
	t_node 	node;

	(void)ac;
	(void)av;
	(void)envp;

	token1.type = 1;
	token1.str = malloc(sizeof(char) * 5);
	token1.str = "echo";
	token1.next = &token2;

	token2.type = 1;
	token2.str = malloc(sizeof(char) * 5);
	token2.str = "test";
	token2.next = &token3;

	token3.type = 1;
	token3.str = malloc(sizeof(char) * 6);
	token3.str = "hello";
	token3.next = NULL;

	node.type = 1;
	node.lnode = NULL;
	node.rnode = NULL;
	node.data = &token1;

	if (builtin_echo(&node))
		return (1);
	return (0);
}
