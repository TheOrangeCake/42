/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:53:48 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/20 12:44:52 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// placeholder
char	*replace_dollar(char *str)
{
	char	*new_str;

	new_str = malloc(sizeof(char) * 12);
	new_str = "hello world";
	free(str);
	return (new_str);
}

int	check_dollar(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '$' && !ft_isspace(str[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

void	echo_flag_n(t_node *node)
{
	(void)node;
	printf("with n\n");
}

void	echo_no_flag(t_node *node)
{
	while (node->data != NULL)
	{
		// if(check_dollar(node->data->str))
		// 	node->data->str = replace_dollar(node->data->str);
		printf("%s\n", node->data->str);
		node->data = node->data->next;
	}
}

int	builtin_echo(t_node *node)
{
	// printf("%s\n", node->data->str);
	// node->data = node->data->next;
	// printf("%s\n", node->data->str);
	// node->data = node->data->next;
	// printf("%s\n", node->data->str);
	node->data = node->data->next;
	if (!ft_strncmp(node->data->str, "-n", 3))
		echo_flag_n(node);
	else
		echo_no_flag(node);
	return (0);
}
