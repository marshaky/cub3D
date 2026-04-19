/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:56:35 by aramarak          #+#    #+#             */
/*   Updated: 2026/04/17 19:59:17 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error_outputs.h"

int	parse_rgb_value(char *raw, int *value)
{
	char	*trimmed;

	trimmed = ft_strtrim(raw, " \n\t");
	if (!trimmed || !is_str_digit(trimmed))
		return (free(trimmed), printf(COL_ERR), ERROR);
	*value = ft_atoi(trimmed);
	free(trimmed);
	if (*value < 0 || *value > 255)
		return (printf(COL_VAL_ERR), ERROR);
	return (0);
}

int	parse_color(char *line, int *color)
{
	char	**rgb;
	int		vals[3];
	int		i;

	line++;
	while (*line && ft_isspace(*line))
		line++;
	rgb = ft_split(line, ',');
	if (!rgb || ft_arrlen(rgb) != 3)
		return (free_split(rgb), printf(COL_ERR), ERROR);
	i = 0;
	while (i < 3)
	{
		if (parse_rgb_value(rgb[i], &vals[i]) != 0)
			return (free_split(rgb), ERROR);
		i++;
	}
	free_split(rgb);
	*color = (vals[0] << 16) | (vals[1] << 8) | vals[2];
	return (0);
}
