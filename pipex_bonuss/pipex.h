/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:47:35 by slevaslo          #+#    #+#             */
/*   Updated: 2023/03/22 21:43:08 by slevaslo         ###   ########.fr       */
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
	int	prev;
	int	cmds;
	int	fd_out;
	int	fd_in;
	int	here_doc[2];
	int	is_here_doc;
}t_data;

void	exec_process(t_data *data, char *str, char **envp, int *pipes);
void	not_find(char **mycmdargs);
void	error(void);
void	ft_freetab(char **str);
char	*find_path(char *cmd, char **envp);
char	*path_is_ok(char **paths, char *cmd);
void	process(char **argv, char **envp, t_data *data);
char	*ft_strjoin(char const *s1, char const *s2);
void	here_doc(char *argv, t_data *data);
void	second_part_dupnclose(int i, int pipes[2], t_data *data);
#endif
