/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:56:33 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/08 13:58:52 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include "sys/wait.h"
# include "stdio.h"
# include "errno.h"

typedef struct s_pipex
{
	int		fdi;
	int		fdo;
	int		pipe1[2];
	int		pipe2[2];
	int		pipe3[2];
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid3;
	char	*path_string;
	char	**paths;
	char	*cmd_path;
	char	**cmd;
	int		i;
	char	*line;
	int		status;
	int		code;
	int		count;
	char	*copy;
	char	*temp;
}	t_pipex;

void	free_split(char **list);
void	free_exit(t_pipex pipex, int code);
void	exit_unlink(char *file);
void	close_pipe1(t_pipex pipex);
void	close_pipe2(t_pipex pipex);
void	close_fd(t_pipex pipex);

char	*find_paths(char **envp);
int		we_gonna_fork_this(t_pipex pipex, int ac, char **av, char **envp);
void	wait_all(t_pipex pipex, int *status, int ac);
void	loop2(t_pipex *pipex, int ac, char **av, char **envp);
char	**cmd_list(t_pipex pipex, char *cmd);

char	**awk_case(t_pipex pipex, char *cmd);

void	process1(t_pipex pipex, char **av, char **envp);
void	process2(t_pipex pipex, int count, char **av, char **envp);
void	process3(t_pipex pipex, int ac, char **av, char **envp);

#endif