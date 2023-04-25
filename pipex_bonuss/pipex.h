/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:47:35 by slevaslo          #+#    #+#             */
/*   Updated: 2023/04/13 17:15:26 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <stddef.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct data
{
	int		prev;
	int		cmds;
	int		fd_out;
	int		fd_in;
	int		here_doc[2];
	int		pipes[2];
	int		is_here_doc;
	int		*pid;
	char	*fd_ch;
	char	*fd_in_ch;
}t_data;

void	exec_process(t_data *data, char *str, char **envp);
void	not_find(char **mycmdargs);
void	error(t_data *data);
void	ft_freetab(char **str);
char	*find_path(char *cmd, char **envp, t_data *data);
char	*path_is_ok(char **paths, char *cmd);
void	process(char **argv, char **envp, t_data *data);
char	*ft_strjoin(char const *s1, char const *s2);
void	here_doc(char *argv, t_data *data);
void	second_part_dupnclose(int i, t_data *data);
void	close_fd(int *fd);
#endif
