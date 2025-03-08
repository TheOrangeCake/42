/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_helper2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 06:16:01 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/08 13:58:57 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**cmd_list(t_pipex pipex, char *cmd)
{
	if (!ft_strncmp(cmd, "awk", 3))
		pipex.cmd = awk_case(pipex, cmd);
	else
		pipex.cmd = ft_split(cmd, ' ');
	if (pipex.cmd == NULL)
		return (NULL);
	return (pipex.cmd);
}

void	close_fd(t_pipex pipex)
{
	close(pipex.fdi);
	close(pipex.fdo);
}

char	*find_paths(char **envp)
{
	if (envp == NULL)
		return ("/");
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return ("/");
}

void	wait_all(t_pipex pipex, int *status, int ac)
{
	waitpid(pipex.pid1, status, 0);
	if (ac > 5)
	{
		while (pipex.i-- >= 3)
			waitpid(pipex.pid2, status, 0);
	}
	waitpid(pipex.pid3, status, 0);
}

void	loop2(t_pipex *pipex, int ac, char **av, char **envp)
{
	while (pipex->i < (ac - 2))
	{
		if (pipe(pipex->pipe2) < 0)
			free_exit(*pipex, 1);
		pipex->pid2 = fork();
		if (pipex->pid2 < 0)
			free_exit(*pipex, 1);
		if (pipex->pid2 == 0)
			process2(*pipex, pipex->i, av, envp);
		close_pipe1(*pipex);
		pipex->pipe1[0] = pipex->pipe2[0];
		pipex->pipe1[1] = pipex->pipe2[1];
		pipex->i++;
	}
}
