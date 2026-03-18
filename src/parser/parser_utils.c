/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marshaky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:21:39 by marshaky          #+#    #+#             */
/*   Updated: 2026/03/18 13:21:48 by marshaky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_config_line(char *line)
{
	if (!line || line[0] == '\n')
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (1);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

int	is_map_line(char *line)
{
	int	i;

	if (!line || line[0] == '\n')
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (i > 0);
}

static int	parse_color(char *line, int *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		i;

	line++;
	while (*line == ' ')
		line++;
	rgb = ft_split(line, ',');
	if (!rgb)
		return (ERROR);
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
		return (free_split(rgb), printf("Error\nInvalid color format\n"), ERROR);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (printf("Error\nColor values must be 0-255\n"), ERROR);
	*color = (r << 16) | (g << 8) | b;
	return (0);
}

int	parse_config_line(t_map *map, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && !map->tex_path_no)
		map->tex_path_no = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "SO ", 3) == 0 && !map->tex_path_so)
		map->tex_path_so = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "WE ", 3) == 0 && !map->tex_path_we)
		map->tex_path_we = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "EA ", 3) == 0 && !map->tex_path_ea)
		map->tex_path_ea = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "F ", 2) == 0 && map->floor_color == 0)
	{
		if (parse_color(line, &map->floor_color) != 0)
			return (ERROR);
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && map->ceil_color == 0)
	{
		if (parse_color(line, &map->ceil_color) != 0)
			return (ERROR);
	}
	else
		return (printf("Error\nDuplicate or invalid config line\n"), ERROR);
	return (0);
}

int	add_map_line(t_map *map, char *line)
{
	char	**new_grid;
	int		i;
	int		len;
	char	*trimmed;

	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
		return (ERROR);
	len = 0;
	while (map->grid && map->grid[len])
		len++;
	new_grid = malloc(sizeof(char *) * (len + 2));
	if (!new_grid)
		return (free(trimmed), ERROR);
	i = 0;
	while (i < len)
	{
		new_grid[i] = map->grid[i];
		i++;
	}
	new_grid[i] = trimmed;
	new_grid[i + 1] = NULL;
	free(map->grid);
	map->grid = new_grid;
	if ((int)ft_strlen(trimmed) > map->width)
		map->width = ft_strlen(trimmed);
	map->height = len + 1;
	return (0);
}