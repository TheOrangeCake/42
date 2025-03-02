/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:52:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/02 15:32:25 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**cmd_list(t_pipex pipex, char *cmd)
{
	pipex.cmd_list = ft_split(cmd, ' ');
	if (pipex.cmd_list == NULL)
		free_exit(pipex);
	return (pipex.cmd_list);
}

char	*cmd_path(t_pipex pipex, char *cmd)
{
	char	*temp;

	while (pipex.paths != NULL)
	{
		temp = ft_strjoin(*pipex.paths, "/");
		if (temp == NULL)
		{
			free_split(pipex.cmd_list);
			free_exit(pipex);
		}
		pipex.cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (pipex.cmd_path == NULL)
		{
			free_split(pipex.cmd_list);
			free_exit(pipex);
		}
		if (access(pipex.cmd_path, 0) == 0)
			return (pipex.cmd_path);
		free(pipex.cmd_path);
		pipex.paths++;
	}
	free_exit(pipex);
	return (NULL);
}

void	process1(t_pipex pipex, char **av, char **envp)
{
	if (pipex.error = dup2(pipex.fd_in, 0) < 0)
		free_exit(pipex);
	if (dup2(pipex.pipe1[1], 1) < 0)
		free_exit(pipex);
	close_pipe1(pipex);
	close_pipe2(pipex);
	pipex.cmd_list = cmd_list(pipex, av[2]);
	pipex.cmd_path = cmd_path(pipex, pipex.cmd_list[0]);
	pipex.error = execve(pipex.cmd_path, pipex.cmd_list, envp);
	free(pipex.cmd_path);
	free_split(pipex.cmd_list);
	if (pipex.error < 0)
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
	pipex.cmd_path = cmd_path(pipex, pipex.cmd_list[0]);
	pipex.error = execve(pipex.cmd_path, pipex.cmd_list, envp);
	free(pipex.cmd_path);
	free_split(pipex.cmd_list);
	if (pipex.error < 0)
		free_exit(pipex);
}

void	process3(t_pipex pipex, int count, char **av, char **envp)
{
	if (dup2(pipex.pipe1[0], 0) < 0)
		free_exit(pipex);
	close_pipe1(pipex);
	close_pipe2(pipex);
	if (dup2(pipex.fd_out, 1) < 0)
		free_exit(pipex);
	pipex.cmd_list = cmd_list(pipex, av[count]);
	pipex.cmd_path = cmd_path(pipex, pipex.cmd_list[0]);
	pipex.error = execve(pipex.cmd_path, pipex.cmd_list, envp);
	free(pipex.cmd_path);
	free_split(pipex.cmd_list);
	if (pipex.error < 0)
		free_exit(pipex);
}
