/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:52:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/01 00:54:42 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_exit(t_pipex pipex)
{
	free_split(pipex.paths);
	close(pipex.fd_in);
	close(pipex.fd_out);
	close_pipe1(pipex);
	close_pipe2(pipex);
	write(2, "Error\n", 6);
	exit (1);
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
