/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:56:11 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/05 12:57:54 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_paths(char **envp)
{
	if (envp == NULL)
		return ("/usr/bin:/bin");
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
			return (*envp + 5);
		envp++;
	}
	return ("/usr/bin:/bin");
}

void	we_gonna_fork_this(t_pipex pipex, int ac, char **av, char **envp)
{
	(void)ac;
	pipex.i = 3;
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		process1(pipex, av, envp);
	pipex.pid3 = fork();
	if (pipex.pid3 == 0)
		process3(pipex, pipex.i, av, envp);
	close_pipe1(pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid3, NULL, 0);
	free_split(pipex.paths);
	close(pipex.fd_in);
	close(pipex.fd_out);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac == 5 && ft_strncmp(av[1], "/dev/urandom", 12))
	{
		if (!ft_strncmp(av[1], "/dev/stdin", 10))
			return (stdin_case(pipex, ac, av, envp), 0);
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
		return (ft_printf("Input error\n"), 1);
	return (0);
}

// ./pipex file1.txt "cat" "grep a1" file2.txt
// < file1.txt cat | grep a1 > file2.txt

// ./pipex file1.txt "cat" "grep a1" "tr '[:lower:]' '[:upper:]'" file2.txt

// ./pipex file1.txt "cat" "grep a1" 
// "tr '[:lower:]' '[:upper:]'" "wc -w" file2.txt

// < file1.txt cat | grep a1 | tr '[:lower:]' '[:upper:]' | wc -w > file2.txt