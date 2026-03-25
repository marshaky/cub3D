/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:31:20 by aramarak          #+#    #+#             */
/*   Updated: 2026/03/21 11:00:52 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)s + i);
	while (i > 0)
	{
		if (s[i - 1] == (char)c)
			return ((char *)s + i - 1);
		i--;
	}
	return (NULL);
}
