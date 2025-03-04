/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:31:51 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/04 13:39:21 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	stdin_read(t_pipex pipex)
{
	if (dup2(pipex.fd_in, 1) < 0)
		exit_unlink(".temp");
	while (1)
	{
		pipex.line = get_next_line(0);
		if (pipex.line == NULL)
		{
			free(pipex.line);
			get_next_line(-100);
			break ;
		}
		ft_printf("%s", pipex.line);
		free(pipex.line);
	}
}

void	stdin_case(t_pipex pipex, int ac, char **av, char **envp)
{
	pipex.fd_in = open(".temp", O_CREAT | O_TRUNC | O_RDWR, 0000644);
	if (pipex.fd_in < 0)
		exit(1);
	stdin_read(pipex);
	pipex.fd_out = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0000644);
	if (pipex.fd_out < 0)
		exit_unlink(".temp");
	if (pipe(pipex.pipe1) < 0)
		exit_unlink(".temp");
	pipex.path_string = find_paths(envp);
	pipex.paths = ft_split(pipex.path_string, ':');
	if (pipex.paths == NULL)
		exit_unlink(".temp");
	close(pipex.fd_in);
	pipex.fd_in = open(".temp", O_RDONLY);
	we_gonna_fork_this(pipex, ac, av, envp);
	if (unlink(".temp") < 0)
	{
		perror("Unlink eror");
		exit(1);
	}
}

char	**awk_case(t_pipex pipex, char *cmd)
{
	int	i;

	i = 0;
	pipex.cmd_list = malloc(sizeof(char *) * 4);
	if (pipex.cmd_list == NULL)
		free_exit(pipex);
	pipex.cmd_list[0] = ft_strdup("awk");
	if (pipex.cmd_list[0] == NULL)
		free_exit(pipex);
	while (*cmd != '\'')
		cmd++;
	while (cmd[i] != '\0')
		i++;
	if (cmd[i] == '\'')
	{
		pipex.cmd_list[1] = ft_strdup(cmd);
		pipex.cmd_list[2] = NULL;
	}
	else
	{
		
	}
	return (pipex.cmd_list);
}
