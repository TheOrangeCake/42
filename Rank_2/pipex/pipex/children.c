/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:52:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/05 20:42:08 by hoannguy         ###   ########.fr       */
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
	char	*temp;
	int		i;

	i = 0;
	while (pipex.paths[i] != NULL && cmd != NULL)
	{
		temp = ft_strjoin(pipex.paths[i], "/");
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
		if (access(pipex.cmd_path, F_OK) == 0)
			return (pipex.cmd_path);
		free(pipex.cmd_path);
		i++;
	}
	pipex.exit_code = 127;
	return (free_split(pipex.cmd_list), free_exit(pipex), NULL);
}

void	process1(t_pipex pipex, char **av, char **envp)
{
	pipex.error = 0;
	if (dup2(pipex.fd_in, 0) < 0)
		free_exit(pipex);
	if (dup2(pipex.pipe1[1], 1) < 0)
		free_exit(pipex);
	close_pipe1(pipex);
	pipex.cmd_list = cmd_list(pipex, av[2]);
	if (pipex.cmd_list == NULL)
		free_exit(pipex);
	pipex.cmd_path = cmd_path(pipex, pipex.cmd_list[0]);
	if (pipex.cmd_path != NULL)
		pipex.error = execve(pipex.cmd_path, pipex.cmd_list, envp);
	free(pipex.cmd_path);
	free_split(pipex.cmd_list);
	if (pipex.error < 0)
		free_exit(pipex);
}

void	process3(t_pipex pipex, int count, char **av, char **envp)
{
	pipex.error = 0;
	if (dup2(pipex.pipe1[0], 0) < 0)
		free_exit(pipex);
	close_pipe1(pipex);
	if (dup2(pipex.fd_out, 1) < 0)
		free_exit(pipex);
	pipex.cmd_list = cmd_list(pipex, av[count]);
	if (pipex.cmd_list == NULL)
		free_exit(pipex);
	pipex.cmd_path = cmd_path(pipex, pipex.cmd_list[0]);
	if (pipex.cmd_path != NULL)
		pipex.error = execve(pipex.cmd_path, pipex.cmd_list, envp);
	free(pipex.cmd_path);
	free_split(pipex.cmd_list);
	if (pipex.error < 0)
		free_exit(pipex);
}
