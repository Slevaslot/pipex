/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 13:37:57 by slevaslo          #+#    #+#             */
/*   Updated: 2023/03/25 15:11:05 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	search_for_abs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	not_find(char **mycmdargs)
{
	if (errno == 13)
		ft_putstr_fd("\033[31;5mpipex\033[0m : permission denied: \n", 2);
	else
		ft_putstr_fd("\033[31;5mpipex\033[0m : command not found: \n", 2);
	if (mycmdargs[0][0] != '\0')
	{
		ft_putstr_fd(mycmdargs[0], 2);
		clearmem(mycmdargs);
	}
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

static void	clearmemory(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static size_t	wordcount(char const *s, char c)
{
	size_t	i;
	size_t	j;

	j = 1;
	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != c && s[i])
			i++;
		j++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	str = malloc(sizeof(char *) * wordcount(s, c));
	if (!str || !s)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		start = i;
		while (s[i] != c && s[i])
			i++;
		str[j] = ft_substr(s, start, i - start);
		if (!str[j++])
			clearmemory(str);
	}
	str[j] = 0;
	return (str);
}

// int	main()
// {
// 	// ft_split("  d dj dk", ' ');
// 	char **ret = ft_split(NULL, ' ');
// 	(void)ret;
// 	// printf("---> (%s)", ret[0]);
// }
