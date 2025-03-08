/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_children_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:52:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/08 14:02:05 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*cmd_path_helper(t_pipex pipex)
{
	while (pipex.copy != NULL)
	{
		pipex.cmd_path = ft_strjoin(pipex.copy, pipex.line);
		if (pipex.cmd_path == NULL)
			free(pipex.line);
		if (pipex.cmd_path == NULL)
			return (free_split(pipex.cmd), free_exit(pipex, 1), NULL);
		if (access(pipex.cmd_path, F_OK) == 0)
		{
			if (access(pipex.cmd_path, X_OK) == 0)
				return (pipex.cmd_path);
			else
				return (free_split(pipex.cmd), free_exit(pipex, 126), NULL);
		}
		free(pipex.cmd_path);
		pipex.temp = ft_strrchr(pipex.copy, '/');
		if (pipex.temp != NULL)
			*pipex.temp = '\0';
		else
		{
			free(pipex.copy);
			break ;
		}
	}
	return (NULL);
}

char	*cmd_path(t_pipex pipex, char *cmd)
{
	pipex.count = 0;
	if (cmd != NULL && cmd[0] != '/' )
		pipex.line = ft_strjoin("/", cmd);
	else if (cmd != NULL)
		pipex.line = ft_strdup(cmd);
	else
	{
		pipex.code = 127;
		return (free_split(pipex.cmd), free_exit(pipex, 1), NULL);
	}
	if (pipex.line == NULL)
		return (free_split(pipex.cmd), free_exit(pipex, 1), NULL);
	while (pipex.paths[pipex.count] != NULL)
	{
		pipex.copy = ft_strdup(pipex.paths[pipex.count]);
		if (pipex.copy == NULL)
			return (free_split(pipex.cmd), free_exit(pipex, 1), NULL);
		pipex.cmd_path = cmd_path_helper(pipex);
		if (pipex.cmd_path != NULL)
			return (pipex.cmd_path);
		pipex.count++;
	}
	free(pipex.line);
	return (free_split(pipex.cmd), free_exit(pipex, 127), NULL);
}

void	process1(t_pipex pipex, char **av, char **envp)
{
	if (dup2(pipex.fdi, 0) < 0)
		free_exit(pipex, 1);
	if (dup2(pipex.pipe1[1], 1) < 0)
		free_exit(pipex, 1);
	close_pipe1(pipex);
	pipex.cmd = cmd_list(pipex, av[2]);
	if (pipex.cmd == NULL)
		free_exit(pipex, 1);
	pipex.cmd_path = cmd_path(pipex, pipex.cmd[0]);
	if (pipex.cmd_path != NULL)
		execve(pipex.cmd_path, pipex.cmd, envp);
	free(pipex.cmd_path);
	free_split(pipex.cmd);
	free_exit(pipex, 1);
}

void	process2(t_pipex pipex, int count, char **av, char **envp)
{
	if (dup2(pipex.pipe1[0], 0) < 0)
		free_exit(pipex, 1);
	if (dup2(pipex.pipe2[1], 1) < 0)
		free_exit(pipex, 1);
	close_pipe1(pipex);
	close_pipe2(pipex);
	pipex.cmd = cmd_list(pipex, av[count]);
	if (pipex.cmd == NULL)
		free_exit(pipex, 1);
	pipex.cmd_path = cmd_path(pipex, pipex.cmd[0]);
	if (pipex.cmd_path != NULL)
		execve(pipex.cmd_path, pipex.cmd, envp);
	free(pipex.cmd_path);
	free_split(pipex.cmd);
	free_exit(pipex, 1);
}

void	process3(t_pipex pipex, int count, char **av, char **envp)
{
	if (dup2(pipex.pipe1[0], 0) < 0)
		free_exit(pipex, 1);
	close_pipe1(pipex);
	if (dup2(pipex.fdo, 1) < 0)
		free_exit(pipex, 1);
	pipex.cmd = cmd_list(pipex, av[count]);
	if (pipex.cmd == NULL)
		free_exit(pipex, 1);
	pipex.cmd_path = cmd_path(pipex, pipex.cmd[0]);
	if (pipex.cmd_path != NULL)
		execve(pipex.cmd_path, pipex.cmd, envp);
	free(pipex.cmd_path);
	free_split(pipex.cmd);
	free_exit(pipex, 1);
}
