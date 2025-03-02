/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:56:11 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/02 17:13:20 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_paths(char **envp)
{
	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	return (*envp + 5);
}

void	we_gonna_fork_this(t_pipex pipex, int ac, char **av, char **envp)
{
	pipex.i = 3;
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		process1(pipex, av, envp);
	if (ac > 5)
	{
		while (pipex.i < (ac - 2))
		{
			if (pipe(pipex.pipe2) < 0)
				free_exit(pipex);
			pipex.pid2 = fork();
			if (pipex.pid2 == 0)
				process2(pipex, pipex.i, av, envp);
			close_pipe1(pipex);
			pipex.pipe1[0] = pipex.pipe2[0];
			pipex.pipe1[1] = pipex.pipe2[1];
			pipex.i++;
		}
	}
	pipex.pid3 = fork();
	if (pipex.pid3 == 0)
		process3(pipex, pipex.i, av, envp);
	free_split(pipex.paths);
	close(pipex.fd_in);
	close(pipex.fd_out);
}

void	bonus_read(t_pipex pipex, char *LIMITER)
{
	if (dup2(pipex.fd_in, 1) < 0)
	{
		unlink(".temp");
		exit(1);
	}
	while (1)
	{
		pipex.line = get_next_line(0);
		if (pipex.line == NULL
			|| !ft_strncmp(pipex.line, LIMITER, ft_strlen(LIMITER)))
		{
			free(pipex.line);
			get_next_line(-100);
			break ;
		}
		ft_printf("%s", pipex.line);
		free(pipex.line);
	}
}

void	bonus(t_pipex pipex, int ac, char **av, char **envp)
{
	if (ac < 6)
		exit(1);
	pipex.fd_in = open(".temp", O_CREAT | O_TRUNC | O_RDWR, 0000644);
	if (pipex.fd_in < 0)
		exit(1);
	bonus_read(pipex, av[2]);
	pipex.fd_out = open(av[ac - 1], O_CREAT | O_APPEND | O_WRONLY, 0000644);
	if (pipex.fd_out < 0)
		exit(1);
	if (pipe(pipex.pipe1) < 0)
		exit(1);
	pipex.path_string = find_paths(envp);
	pipex.paths = ft_split(pipex.path_string, ':');
	if (pipex.paths == NULL)
		exit(1);
	av++;
	ac--;
	close(pipex.fd_in);
	pipex.fd_in = open(".temp", O_RDONLY);
	we_gonna_fork_this(pipex, ac, av, envp);
	unlink(".temp");
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac >= 5)
	{
		if (!ft_strncmp(av[1], "here_doc", 8))
			return (bonus(pipex, ac, av, envp), 0);
		pipex.fd_in = open(av[1], O_RDONLY);
		if (pipex.fd_in < 0)
			exit(1);
		pipex.fd_out = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0000644);
		if (pipex.fd_out < 0)
			exit(1);
		if (pipe(pipex.pipe1) < 0)
			exit(1);
		pipex.path_string = find_paths(envp);
		pipex.paths = ft_split(pipex.path_string, ':');
		if (pipex.paths == NULL)
			exit(1);
		we_gonna_fork_this(pipex, ac, av, envp);
	}
	else
		exit(1);
	return (0);
}

// ./pipex file1.txt "cat" "grep a1" file2.txt
// < file1.txt cat | grep a1 > file2.txt

// ./pipex file1.txt "cat" "grep a1" "tr '[:lower:]' '[:upper:]'" file2.txt

// ./pipex file1.txt "cat" "grep a1" 
// "tr '[:lower:]' '[:upper:]'" "wc -w" file2.txt

// < file1.txt cat | grep a1 | tr '[:lower:]' '[:upper:]' | wc -w > file2.txt