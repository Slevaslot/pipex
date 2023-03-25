/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:38:08 by slevaslo          #+#    #+#             */
/*   Updated: 2023/03/25 15:01:06 by slevaslo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t			i;
	size_t			j;
	char			*big;
	char			*lit;

	i = 0;
	j = 0;
	if (!str && n == 0)
		return (0);
	big = (char *)str;
	lit = (char *)to_find;
	if (lit[j] == '\0')
		return (&big[i]);
	while (big[i] && i < n)
	{
		while (lit[j] && i + j < n && big[i + j] == lit[j])
			j++;
		if (lit[j] == '\0')
			return ((char *)&big[i]);
		j = 0;
		i++;
	}
	return (NULL);
}

void	error(void)
{
	perror("\033[31;5mError\033[0m");
	exit(EXIT_FAILURE);
}

char	*str_remove_whitespace(char *str)
{
	int		i;
	char	*strr;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	strr = malloc(sizeof(char) * i);
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] < 32)
			return (strr);
		strr[i] = str[i];
		i++;
	}
	strr[i] = '\0';
	return (strr);
}

void	clearmem(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		free(str[i]);
	}
	free(str);
}
