/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:47:06 by hoannguy          #+#    #+#             */
/*   Updated: 2025/04/23 15:52:18 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

int	transform_env(t_env **env, char **envp)
{
	t_env	*var;

	while (*envp != NULL)
	{
		var = malloc(sizeof(t_env));
		if (var == NULL)
			return (perror("Error"), ft_lstclear_env(env), 1);
		var->key = ft_substring_key(*envp);
		if (var->key == NULL)
			return (perror("Error"), ft_lstclear_env(env), 1);
		var->value = ft_substring_value(*envp);
		if (var->value == NULL)
			return (perror("Error"), ft_lstclear_env(env), 1);
		var->exported = true;
		var->next = NULL;
		ft_lstadd_back_env(env, var);
		envp++;
	}
	return (0);
}
