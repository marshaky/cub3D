/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 11:02:51 by aramarak          #+#    #+#             */
/*   Updated: 2026/03/21 11:02:51 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*arr;

	if (num != 0 && (size_t) - 1 / num < size)
		return (NULL);
	arr = (void *)malloc(size * num);
	if (!arr)
		return (NULL);
	ft_bzero(arr, size * num);
	return (arr);
}
