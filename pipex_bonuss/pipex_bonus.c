/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:48:01 by slevaslo          #+#    #+#             */
/*   Updated: 2023/04/13 17:15:40 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_process(t_data *data, char *str, char **envp)
{
	char	**mycmdargs;
	char	*path;

	mycmdargs = ft_split(str, ' ');
	if (!mycmdargs)
		return (ft_freetab(mycmdargs));
	if (!mycmdargs[0])
	{
		free(data->pid);
		not_find(mycmdargs);
	}
	path = find_path(mycmdargs[0], envp, data);
	if (!path)
	{
		free(data->pid);
		not_find(mycmdargs);
	}
	execve(path, mycmdargs, envp);
	ft_freetab(mycmdargs);
	free(data->pid);
	exit(1);
}

void	dupncloses(int i, t_data *data)
{
	if (i == 0)
	{
		if (data->is_here_doc == 0)
			data->fd_in = open(data->fd_in_ch, O_RDONLY, 0644);
		if (data->fd_in == -1)
		{
			close_fd(&data->pipes[0]);
			close_fd(&data->pipes[1]);
			close_fd(&data->here_doc[0]);
			error(data);
		}
		dup2(data->fd_in, STDIN_FILENO);
		close_fd(&data->fd_in);
		dup2(data->pipes[1], STDOUT_FILENO);
		close_fd(&data->pipes[1]);
		close_fd(&data->pipes[0]);
	}
	else
		second_part_dupnclose(i, data);
}

void	process(char **argv, char **envp, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmds)
	{
		if (i != data->cmds - 1)
			pipe(data->pipes);
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			error(data);
		else if (data->pid[i] == 0)
		{
			dupncloses(i, data);
			exec_process(data, argv[i + (2 + data->is_here_doc)], envp);
		}
		close_fd(&data->pipes[1]);
		close_fd(&data->prev);
		data->prev = data->pipes[0];
		if (i == 0 && data->is_here_doc == 1)
			close_fd(&data->here_doc[0]);
		i++;
	}
	i = -1;
	while (++i < data->cmds)
		waitpid(data->pid[i], NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (argc < 5)
	{
		ft_putstr_fd("\033[31;5merror(t_data *data)\033[0m Usage: ", 1);
		ft_putstr_fd("<infile> cmd1 | cmd2 | ... | cmdN > <outfile>\n", 1);
		exit(EXIT_FAILURE);
	}
	data.prev = -1;
	data.fd_in_ch = argv[1];
	data.fd_ch = argv[argc - 1];
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		here_doc(argv[2], &data);
	else
		data.is_here_doc = 0;
	data.cmds = argc - (3 + data.is_here_doc);
	data.pid = malloc(sizeof(int) * data.cmds);
	if (data.pid == NULL)
		exit(EXIT_FAILURE);
	process(argv, envp, &data);
	free(data.pid);
	return (0);
}
