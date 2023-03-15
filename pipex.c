/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:14:39 by slevaslo          #+#    #+#             */
/*   Updated: 2023/03/15 16:22:17 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*fpath;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		fpath = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(fpath, F_OK) == 0)
		{
			clearmem(paths);
			return (fpath);
		}
		free(fpath);
		i++;
	}
	clearmem(paths);
	return (0);
}

void	exec_process(char *str, char **envp)
{
	char	**mycmdargs;
	char	*path;
	int		i;

	i = -1;
	mycmdargs = ft_split(str, ' ');
	path = find_path(mycmdargs[0], envp);
	if (path == 0)
	{
		while (mycmdargs[++i])
			free(mycmdargs[i]);
		free(mycmdargs);
		error();
	}
	execve(path, mycmdargs, envp);
}

void	parent_process(char **str, char **str1, int *end)
{
	int	outfile;

	outfile = open(str[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		error();
	if (dup2(outfile, STDOUT_FILENO) == -1)
		error();
	if (dup2(end[0], STDIN_FILENO) == -1)
		error();
	close (end[1]);
	exec_process(str[3], str1);
}

void	child_process(char **str, char **str1, int *end)
{
	int	infile;

	infile = open(str[1], O_RDONLY, 0777);
	if (infile == -1)
		error();
	if (dup2(end[1], STDOUT_FILENO) == -1)
		error();
	if (dup2(infile, STDIN_FILENO) == -1)
		error();
	close(end[0]);
	exec_process(str[2], str1);
}

int	main(int ac, char **str, char **envp)
{
	int		end[2];
	pid_t	pid_child;
	pid_t	pid_child1;

	if (ac != 5)
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	pipe(end);
	pid_child = fork();
	if (pid_child == -1)
		error();
	if (pid_child == 0)
		child_process(str, envp, end);
	pid_child1 = fork();
	if (pid_child == -1)
		error();
	if (pid_child1 == 0)
		parent_process(str, envp, end);
	close(end[1]);
	close(end[0]);
	waitpid(pid_child, NULL, 0);
	waitpid(pid_child1, NULL, 0);
}
