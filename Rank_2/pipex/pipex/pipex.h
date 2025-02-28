/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:56:33 by hoannguy          #+#    #+#             */
/*   Updated: 2025/02/28 18:35:31 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
// # include "<sys/wait.h>"

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	int		pipe1[2];
	int		pipe2[2];
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid3;
	char	*path_string;
	char	**paths;
	char	*cmd_path;
	char	**cmd_list;
	int		error;
}	t_pipex;

void	free_split(char **list);
void	free_exit(t_pipex pipex);
void	close_pipe1(t_pipex pipex);
void	close_pipe2(t_pipex pipex);

void	process1(t_pipex pipex, char **av, char **envp);
void	process2(t_pipex pipex, int count, char **av, char **envp);
void	process3(t_pipex pipex, int ac, char **av, char **envp);

#endif