/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:14:14 by slevaslo          #+#    #+#             */
/*   Updated: 2023/03/29 15:13:06 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_cmd(char *str, char **envp)
{
	char	**mycmdargs;
	char	*path;
	int		i;

	i = -1;
	perror("\033[31;5mError\033[0m ");
	if (str[0] == '\0')
		return (not_find(&str));
	mycmdargs = ft_split(str, ' ');
	if (access(str, F_OK | X_OK) == 0)
		path = str;
	else if (search_for_abs(str) == 0)
		path = find_path(mycmdargs[0], envp);
	if (!path)
	{
		if (path == 0)
		{
			while (mycmdargs[++i])
				free(mycmdargs[i]);
			free(mycmdargs);
			not_find(mycmdargs);
		}
	}
	else
		return ;
}
