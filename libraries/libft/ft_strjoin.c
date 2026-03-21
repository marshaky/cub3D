/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:40:47 by aramarak          #+#    #+#             */
/*   Updated: 2026/03/21 11:01:17 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*strjoin;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	strjoin = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1,
			sizeof(char));
	if (!strjoin)
		return (NULL);
	tmp = strjoin;
	while (*s1)
	{
		*tmp = *s1;
		tmp++;
		s1++;
	}
	while (*s2)
	{
		*tmp = *s2;
		tmp++;
		s2++;
	}
	return (strjoin);
}
