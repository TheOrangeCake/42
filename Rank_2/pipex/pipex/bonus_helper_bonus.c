/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_helper_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:52:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/06 06:22:02 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_unlink(char *file)
{
	perror("Error");
	if (unlink(file) < 0)
		perror("Unlink error");
	exit(1);
}

void	free_exit(t_pipex pipex)
{
	perror("Error");
	free_split(pipex.paths);
	close(pipex.fdi);
	close(pipex.fdo);
	unlink(".temp");
	if (pipex.exit_code == 127)
		exit(127);
	exit(1);
}

void	free_split(char **list)
{
	int	i;

	i = 0;
	while (list[i] != NULL)
	{
		free(list[i]);
		i++;
	}
	free(list);
}

void	close_pipe1(t_pipex pipex)
{
	close(pipex.pipe1[0]);
	close(pipex.pipe1[1]);
}

void	close_pipe2(t_pipex pipex)
{
	close(pipex.pipe2[0]);
	close(pipex.pipe2[1]);
}
