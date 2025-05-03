/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:39:54 by hoannguy          #+#    #+#             */
/*   Updated: 2025/05/02 21:24:52 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	case_cd_path(char *path, t_env **env)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*tmp;

	if (chdir(path) != 0)
		return (perror("Error"), 1);
	oldpwd = find_oldpwd(env);
	pwd = find_pwd(env);
//
//
//
	return (0);
}

int	case_cd_previous(t_env **env)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*tmp;

	oldpwd = find_oldpwd(env);
	if (oldpwd == NULL)
		return (printf("bash: cd: OLDPWD not set\n"), 1);
	pwd = find_pwd(env);
	if (pwd != NULL)
		tmp = pwd->value;
	else
	{
		tmp = getcwd(NULL, 0);
		if (tmp == NULL)
			return (perror("Error"), 1);
	}
	if (chdir(oldpwd->value) != 0)
		return (perror("Error"), 1);
	if (pwd != NULL)
		pwd->value = oldpwd->value;
	else
		free(oldpwd->value);
	oldpwd->value = tmp;
	return (0);
}

int	case_cd_home(t_env **env)
{
	(void)env;
	printf("placeholder\n");
	return (0);
}

int	case_cd_no_arg(t_env **env)
{
	(void)env;
	printf("placeholder\n");
	return (0);
}

int	builtin_cd(t_node *node, t_env **env)
{
	if (node->data->next == NULL)
		return (case_cd_no_arg(env));
	if (node->data->next->next != NULL)
		return (printf("bash: cd: too many arguments\n"), 1);
	node->data = node->data->next;
	if (!ft_strncmp(node->data->str, "~", 1))
		return (case_cd_home(env));
	else if (!ft_strncmp(node->data->str, "-", 2))
		return (case_cd_previous(env));
	else
		return (case_cd_path(node->data->str, env));
	return (0);
}
