/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:48:01 by slevaslo          #+#    #+#             */
/*   Updated: 2023/03/22 21:43:39 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_process(t_data *data, char *str, char **envp, int *pipes)
{
	char	**mycmdargs;
	char	*path;

	mycmdargs = ft_split(str, ' ');
	if (!mycmdargs)
		return (ft_freetab(mycmdargs));
	path = find_path(mycmdargs[0], envp);
	if (!path)
	{
		close(data->fd_in);
		close(data->fd_out);
		close(pipes[1]);
		not_find(mycmdargs);
	}
	execve(path, mycmdargs, envp);
}

void	dupncloses(int i, int pipes[2], t_data *data)
{
	if (i == 0)
	{
		if (data->fd_in == -1)
		{
			close(pipes[0]);
			close(pipes[1]);
			close(data->fd_out);
			error();
			return ;
		}
		if (data->fd_in != -1)
		{
			dup2(data->fd_in, STDIN_FILENO);
			close(data->fd_in);
		}
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[1]);
	}
	else
		second_part_dupnclose(i, pipes, data);
	close(pipes[0]);
}

void	savencloses(int i, int pipes[2], t_data *data)
{
	if (i != data->cmds - 1)
	{
		if (data->prev != -1)
			close(data->prev);
		data->prev = pipes[0];
	}
	else
	{
		close(data->prev);
		close(pipes[0]);
	}
}

void	process(char **argv, char **envp, t_data *data)
{
	int	i;
	int	pid;
	int	pipes[2];

	i = 0;
	while (i < data->cmds)
	{
		pipe(pipes);
		pid = fork();
		if (pid == -1)
			error();
		else if (pid == 0)
		{
			dupncloses(i, pipes, data);
			exec_process(data, argv[i + (2 + data->is_here_doc)], envp, pipes);
		}
		close(pipes[1]);
		savencloses(i, pipes, data);
	i++;
	}
	while (i > 0)
	{
		wait(0);
		i--;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 5)
	{
		ft_putstr_fd("\033[31;5mError\033[0m Usage: ", 1);
		ft_putstr_fd("<infile> cmd1 | cmd2 | ... | cmdN > <outfile>\n", 1);
		exit(EXIT_FAILURE);
	}
	data.prev = -1;
	data.fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (data.fd_out == -1)
		return (1);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		here_doc(argv[2], &data);
	else
	{
		data.fd_in = open(argv[1], O_RDONLY);
		data.is_here_doc = 0;
	}
	data.cmds = argc - (3 + data.is_here_doc);
	process(argv, envp, &data);
	close(data.fd_in);
	close(data.fd_out);
	return (0);
}
