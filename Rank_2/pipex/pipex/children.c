/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:52:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/02/27 15:58:46 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**cmd_list(t_pipex pipex, char *cmd)
{
	pipex.cmd_list = ft_split(cmd, ' ');
	if (pipex.cmd_list == NULL)
	{
		free_split(pipex.paths);
		write(2, "Function ft_split failed\n", 25);
		exit (1);
	}
	return (pipex.cmd_list);
}

char	*cmd_path(t_pipex pipex, char *cmd)
{
	char	*temp;

	while (pipex.paths != NULL)
	{
		temp = ft_strjoin(*pipex.paths, "/");
		if (temp == NULL)
			return (write(2, "Function ft_strjoin failed\n", 27), NULL);
		pipex.cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (pipex.cmd_path == NULL)
			return (write(2, "Function ft_strjoin failed\n", 27), NULL);
		if (access(pipex.cmd_path, 0) == 0)
			return (pipex.cmd_path);
		free(pipex.cmd_path);
		pipex.paths++;
	}
	return (NULL);
}

void	process1(t_pipex pipex, char **av, char **envp)
{
	int	error;

	error = dup2(pipex.fd_in, 0);
	if (error < 0)
	{
		free_split(pipex.paths);
		exit (1);
	}
	error = dup2(pipex.pipe[1], 1);
	if (error < 0)
	{
		free_split(pipex.paths);
		exit (1);
	}
	close(pipex.pipe[0]);
	pipex.cmd_list = cmd_list(pipex, av[2]);
	pipex.cmd_path = cmd_path(pipex, pipex.cmd_list[0]);
	if (pipex.cmd_path == NULL)
	{
		free_split(pipex.paths);
		exit (1);
	}
	execve(pipex.cmd_path, pipex.cmd_list, envp);
	free(pipex.cmd_path);
	free_split(pipex.cmd_list);
}

void	process2(t_pipex pipex, char **av, char **envp)
{
	int	error;

	error = dup2(pipex.pipe[0], 0);
	if (error < 0)
	{
		free_split(pipex.paths);
		exit (1);
	}
	error = dup2(pipex.fd_out, 1);
	if (error < 0)
	{
		free_split(pipex.paths);
		exit (1);
	}
	close(pipex.pipe[1]);
	pipex.cmd_list = cmd_list(pipex, av[3]);
	pipex.cmd_path = cmd_path(pipex, pipex.cmd_list[0]);
	if (pipex.cmd_path == NULL)
	{
		free_split(pipex.paths);
		exit (1);
	}
	execve(pipex.cmd_path, pipex.cmd_list, envp);
	free(pipex.cmd_path);
	free_split(pipex.cmd_list);
}
