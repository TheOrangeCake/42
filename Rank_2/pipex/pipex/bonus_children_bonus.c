/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_children_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:52:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/07 23:40:35 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**cmd_list(t_pipex pipex, char *cmd)
{
	if (!ft_strncmp(cmd, "awk", 3))
		pipex.cmd_list = awk_case(pipex, cmd);
	else
		pipex.cmd_list = ft_split(cmd, ' ');
	if (pipex.cmd_list == NULL)
		return (NULL);
	return (pipex.cmd_list);
}

char	*cmd_path(t_pipex pipex, char *cmd)
{
	int		i;
	char	*copy;
	char	*temp;

	i = 0;
	if (cmd != NULL && cmd[0] != '/' )
		pipex.line = ft_strjoin("/", cmd);
	else if (cmd != NULL)
		pipex.line = ft_strdup(cmd);
	if (pipex.line == NULL)
		return (free_split(pipex.cmd_list), free_exit(pipex), NULL);
	while (pipex.paths[i] != NULL)
	{
		copy = ft_strdup(pipex.paths[i]);
		if (copy == NULL)
			return (free_split(pipex.cmd_list), free_exit(pipex), NULL);
		while (copy != NULL)
		{
			pipex.cmd_path = ft_strjoin(copy, pipex.line);
			if (pipex.cmd_path == NULL)
				return (free(pipex.line), free_split(pipex.cmd_list), free_exit(pipex), NULL);
			if (access(pipex.cmd_path, F_OK) == 0)
			{
				if (access(pipex.cmd_path, X_OK) == 0)
					return (pipex.cmd_path);
				else
				{
					pipex.code = 126;
					return (free_split(pipex.cmd_list), free_exit(pipex), NULL);
				}
			}
			free(pipex.cmd_path);
			temp = ft_strrchr(copy, '/');
			if (temp != NULL && *temp != '\0')
				*temp = '\0';
			else
			{
				free(copy);
				break;
			}
		i++;
		}
	}
	free(pipex.line);
	pipex.code = 127;
	return (free_split(pipex.cmd_list), free_exit(pipex), NULL);
}

void	process1(t_pipex pipex, char **av, char **envp)
{
	if (dup2(pipex.fdi, 0) < 0)
		free_exit(pipex);
	if (dup2(pipex.pipe1[1], 1) < 0)
		free_exit(pipex);
	close_pipe1(pipex);
	pipex.cmd_list = cmd_list(pipex, av[2]);
	if (pipex.cmd_list == NULL)
		free_exit(pipex);
	pipex.cmd_path = cmd_path(pipex, pipex.cmd_list[0]);
	if (pipex.cmd_path != NULL)
		execve(pipex.cmd_path, pipex.cmd_list, envp);
	free(pipex.cmd_path);
	free_split(pipex.cmd_list);
	free_exit(pipex);
}

void	process2(t_pipex pipex, int count, char **av, char **envp)
{
	if (dup2(pipex.pipe1[0], 0) < 0)
		free_exit(pipex);
	if (dup2(pipex.pipe2[1], 1) < 0)
		free_exit(pipex);
	close_pipe1(pipex);
	close_pipe2(pipex);
	pipex.cmd_list = cmd_list(pipex, av[count]);
	if (pipex.cmd_list == NULL)
		free_exit(pipex);
	pipex.cmd_path = cmd_path(pipex, pipex.cmd_list[0]);
	if (pipex.cmd_path != NULL)
		execve(pipex.cmd_path, pipex.cmd_list, envp);
	free(pipex.cmd_path);
	free_split(pipex.cmd_list);
	free_exit(pipex);
}

void	process3(t_pipex pipex, int count, char **av, char **envp)
{
	if (dup2(pipex.pipe1[0], 0) < 0)
		free_exit(pipex);
	close_pipe1(pipex);
	if (dup2(pipex.fdo, 1) < 0)
		free_exit(pipex);
	pipex.cmd_list = cmd_list(pipex, av[count]);
	if (pipex.cmd_list == NULL)
		free_exit(pipex);
	pipex.cmd_path = cmd_path(pipex, pipex.cmd_list[0]);
	if (pipex.cmd_path != NULL)
		execve(pipex.cmd_path, pipex.cmd_list, envp);
	free(pipex.cmd_path);
	free_split(pipex.cmd_list);
	free_exit(pipex);
}
