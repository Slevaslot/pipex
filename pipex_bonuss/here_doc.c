/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:34:49 by slevaslo          #+#    #+#             */
/*   Updated: 2023/05/08 15:30:45 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fd(int *fd)
{
	if (*fd < 0)
		return ;
	close(*fd);
	*fd = -1;
}

void	second_part_dupnclose(int i, t_data *data)
{
	if (i == data->cmds - 1)
	{
		data->fd_out = open(data->fd_ch, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->fd_out == -1)
		{
			close_fd(&data->prev);
			error(data);
		}
		dup2(data->prev, STDIN_FILENO);
		close_fd(&data->prev);
		dup2(data->fd_out, STDOUT_FILENO);
		close_fd(&data->fd_out);
	}
	else
	{
		close_fd(&data->pipes[0]);
		dup2(data->prev, STDIN_FILENO);
		close_fd(&data->prev);
		dup2(data->pipes[1], STDOUT_FILENO);
		close_fd(&data->pipes[1]);
	}
}

void	ft_freetab(char **str)
{
	int		i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	ft_putstr_fd_for_here(char *s, char *limiter, int fd)
{
	size_t	i;
	size_t	j;

	if (!s)
		return ;
	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == limiter[j])
		{
			while (s[i] == limiter[j])
			{
				i++;
				j++;
			}
			if (j == ft_strlen(limiter))
				break ;
			i = i - j;
			j = 0;
		}
		write (fd, &s[i], 1);
		i++;
	}
}

void	here_doc(char *argv, t_data *data)
{
	char	*buf;

	data->is_here_doc = 1;
	if (pipe(data->here_doc) == -1)
		return ;
	argv = ft_strjoin(argv, "\n");
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(0, 0);
		if (!buf)
			break ;
		if (!ft_strncmp(argv, buf, ft_strlen(argv) + 1))
			break ;
		ft_putstr_fd(buf, data->here_doc[1]);
		free(buf);
	}
	free(argv);
	free(buf);
	get_next_line(0, 1);
	close(data->here_doc[1]);
	data->fd_in = data->here_doc[0];
}
