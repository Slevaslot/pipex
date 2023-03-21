/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:14:39 by slevaslo          #+#    #+#             */
/*   Updated: 2023/03/20 14:30:23 by slevaslo         ###   ########.fr       */
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
		if (access(fpath, F_OK | X_OK) == 0)
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
	if (str[0] == '\0')
		return (not_find(&str));
	mycmdargs = ft_split(str, ' ');
	if (access(str, F_OK | X_OK) == 0)
		path = str;
	else if (search_for_abs(str) == 0)
		path = find_path(mycmdargs[0], envp);
	if (!path)
	{
		not_find(mycmdargs);
		if (path == 0)
		{
			while (mycmdargs[++i])
				free(mycmdargs[i]);
			free(mycmdargs);
			error();
		}
	}
	else
		execve(path, mycmdargs, envp);
}

void	second_process(char **str, char **str1, int *end)
{
	int	outfile;

	outfile = open(str[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
	{
		close(end[1]);
		close(end[0]);
		error();
	}
	if (dup2(outfile, STDOUT_FILENO) == -1)
		error();
	if (dup2(end[0], STDIN_FILENO) == -1)
		error();
	close (end[1]);
	close(outfile);
	close(end[0]);
	exec_process(str[3], str1);
}

void	first_process(char **str, char **str1, int *end)
{
	int	infile;

	infile = open(str[1], O_RDONLY, 0777);
	if (infile == -1)
	{
		close(end[1]);
		close(end[0]);
		error();
	}
	if (dup2(end[1], STDOUT_FILENO) == -1)
		error();
	if (dup2(infile, STDIN_FILENO) == -1)
		error();
	close(end[0]);
	close(infile);
	close(end[1]);
	exec_process(str[2], str1);
}

int	main(int ac, char **str, char **envp)
{
	int		end[2];
	pid_t	pid_child;
	pid_t	pid_child1;

	if (ac != 5)
	{
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
		return (0);
	}
	pipe(end);
	pid_child = fork();
	if (pid_child == -1)
		error();
	if (pid_child == 0)
		first_process(str, envp, end);
	pid_child1 = fork();
	if (pid_child == -1)
		error();
	if (pid_child1 == 0)
		second_process(str, envp, end);
	close(end[1]);
	close(end[0]);
	waitpid(pid_child, NULL, 0);
	waitpid(pid_child1, NULL, 0);
}
