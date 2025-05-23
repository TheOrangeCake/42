/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:31:51 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/08 14:01:03 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**awk_with_file(t_pipex pipex, int i, char *cmd)
{
	char	*temp;

	i = 0;
	while (!(cmd[i] == '\'' && cmd[i + 1] == ' '))
		i++;
	i++;
	temp = cmd + i + 1;
	cmd[i] = '\0';
	cmd = ft_strtrim(cmd, "'");
	if (cmd == NULL)
		return (NULL);
	pipex.cmd[1] = ft_strdup(cmd);
	if (pipex.cmd[1] == NULL)
		return (NULL);
	if (*temp == '"')
	{
		temp = ft_strtrim(temp, "\"");
		if (temp == NULL)
			return (NULL);
	}
	pipex.cmd[2] = ft_strdup(temp);
	if (pipex.cmd[2] == NULL)
		return (NULL);
	pipex.cmd[3] = NULL;
	return (pipex.cmd);
}

char	**awk_no_file(t_pipex pipex, char *cmd)
{
	char	*temp;

	temp = ft_strtrim(cmd, "'");
	if (temp == NULL)
		return (NULL);
	pipex.cmd[1] = ft_strdup(temp);
	if (pipex.cmd[1] == NULL)
		return (NULL);
	pipex.cmd[2] = NULL;
	return (pipex.cmd);
}

char	**awk_case(t_pipex pipex, char *cmd)
{
	int	i;

	i = 0;
	pipex.cmd = malloc(sizeof(char *) * 4);
	if (pipex.cmd == NULL)
		free_exit(pipex, 1);
	pipex.cmd[0] = ft_strdup("awk");
	if (pipex.cmd[0] == NULL)
	{
		free(pipex.cmd);
		free_exit(pipex, 1);
	}
	while (*cmd != '\'')
		cmd++;
	while (cmd[i + 1] != '\0')
		i++;
	if (cmd[i] == '\'')
		pipex.cmd = awk_no_file(pipex, cmd);
	else
		pipex.cmd = awk_with_file(pipex, i, cmd);
	if (pipex.cmd == NULL)
		return (free_split(pipex.cmd), NULL);
	return (pipex.cmd);
}
