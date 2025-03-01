/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:56:11 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/01 02:06:13 by hoannguy         ###   ########.fr       */
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
	int	i;

	i = 3;
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		process1(pipex, av, envp);
	// waitpid(pipex.pid1, NULL, 0);
	if (ac > 5)
	{
		while(i < (ac - 2))
		{
			pipex.pid2 = fork();
			if (pipex.pid2 == 0)
				process2(pipex, i, av, envp);
			i++;
		}
		// waitpid(pipex.pid2, NULL, 0);
	}
	pipex.pid3 = fork();
	if (pipex.pid3 == 0)
		process3(pipex, i, av, envp);
	// waitpid(pipex.pid2, NULL, 0);
	waitpid(pipex.pid3, NULL, 0);
	free_split(pipex.paths);
	close(pipex.fd_in);
	close(pipex.fd_out);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac >= 5)
	{
		// if (ft_strncmp(av[1], "here_doc", 7))
		// 	return (bonus(pipex, ac, av, envp), 0);
		pipex.fd_in = open(av[1], O_RDONLY);
		if (pipex.fd_in < 0)
			return (write(2, "fail to open infile\n", 20), 1);
		pipex.fd_out = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (pipex.fd_out < 0)
			return (write(2, "fail to open outfile\n", 21), 1);
		if (pipe(pipex.pipe1) < 0)
			return (write(2, "fail to create pipe\n", 20), 1);
		if (pipe(pipex.pipe2) < 0)
			return (write(2, "fail to create pipe\n", 20), 1);
		pipex.path_string = find_paths(envp);
		pipex.paths = ft_split(pipex.path_string, ':');
		if (pipex.paths == NULL)
			return (write(2, "Function ft_split failed\n", 25), 1);
		we_gonna_fork_this(pipex, ac, av, envp);
	}
	else
		write(2, "Not enough argument\n", 20);
	return (0);
}

// 2: ./pipex file1.txt "cat" "grep a1" file2.txt
// < file1.txt cat | grep a1 > file2.txt

// 3: ./pipex file1.txt "cat" "grep a1" "tr '[:lower:]' '[:upper:]'" file2.txt

// 4: ./pipex file1.txt "cat" "grep a1" "tr '[:lower:]' '[:upper:]'" "wc -w" file2.txt

// < file1.txt cat | grep a1 | tr '[:lower:]' '[:upper:]' | wc -w > file2.txt