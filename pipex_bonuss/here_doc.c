/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:34:49 by slevaslo          #+#    #+#             */
/*   Updated: 2023/03/29 15:26:47 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	second_part_dupnclose(int i, int pipes[2], t_data *data)
{
	if (i == data->cmds - 1)
	{
		if (data->fd_out == -1)
		{
			close(pipes[1]);
			close(pipes[0]);
			error();
		}
		dup2(data->prev, STDIN_FILENO);
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->prev);
		close(data->fd_out);
	}
	else
	{
		dup2(data->prev, STDIN_FILENO);
		dup2(pipes[1], STDOUT_FILENO);
		close(data->prev);
		close(pipes[1]);
	}
}

void	ft_freetab(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
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
// void	here_doc_02(char *argv, data *data)
// {
// 	int		file;
// 	char	*buf;
// 	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 777);
// 	if (file < 0)
// 		ft_putstr_fd("ERR_HEREDOC", 2);
// 	while (1)
// 	{
// 		write(1, "heredoc> ", 9);
// 		buf = get_next_line(0);
// 		if (!buf)
// 			break ;
// 		if (!ft_strncmp(argv, buf, ft_strlen(argv)))
// 			break ;
// 		ft_putstr_fd(buf, file);
// 		// write(file, "\n", 1);
// 		free(buf);
// 	}
// 	free(buf);
// 	close(file);
// 	data->fd_in = open(".heredoc_tmp", O_RDONLY);
// 	if (data->fd_in < 0)
// 	{
// 		error();
// 		ft_putstr_fd("ERR_HEREDOC", 2);
// 	}
// }

void	here_doc(char *argv, t_data *data)
{
	char	*buf;

	data->is_here_doc = 1;
	if (pipe (data->here_doc) == -1)
		return ;
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(0);
		if (!buf)
			break ;
		if (!ft_strncmp(argv, buf, ft_strlen(argv)))
			break ;
		ft_putstr_fd(buf, data->here_doc[1]);
		free(buf);
	}
	free(buf);
	close(data->here_doc[1]);
	data->fd_in = data->here_doc[0];
	if (data->fd_in < 0)
	{
		error();
		ft_putstr_fd("ERR_HEREDOC", 2);
	}
}
