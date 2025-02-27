/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:56:33 by hoannguy          #+#    #+#             */
/*   Updated: 2025/02/27 15:58:49 by hoannguy         ###   ########.fr       */
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
	int		pipe[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*path_string;
	char	**paths;
	char	*cmd_path;
	char	**cmd_list;
}	t_pipex;

void	free_split(char **list);
void	process1(t_pipex pipex, char **av, char **envp);
void	process2(t_pipex pipex, char **av, char **envp);

#endif