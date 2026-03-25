/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:58:51 by marshaky          #+#    #+#             */
/*   Updated: 2026/03/21 11:17:46 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

char	*ft_strchr_gnl(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

static char	*ft_strcpy_joined(char *res, char *s1, char *s2)
{
	int	i;
	int	j;

	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	j = 0;
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*res;

	if (!s1)
		return (ft_strdup_gnl(s2));
	if (!s2)
		return (ft_strdup_gnl(s1));
	res = (char *)malloc(sizeof(char) * (ft_strlen_gnl(s1)
				+ ft_strlen_gnl(s2) + 1));
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	res = ft_strcpy_joined(res, s1, s2);
	free(s1);
	return (res);
}

char	*ft_strdup_gnl(const char *str)
{
	char	*s;
	int		i;

	s = (char *)malloc(sizeof(char) * (ft_strlen_gnl(str) + 1));
	if (!s)
		return (NULL);
	i = 0;
	while (str[i])
	{
		s[i] = str[i];
		++i;
	}
	s[i] = '\0';
	return (s);
}
