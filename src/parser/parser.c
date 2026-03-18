/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marshaky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:20:32 by marshaky          #+#    #+#             */
/*   Updated: 2026/03/18 13:45:05 by marshaky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_spawn_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	set_player_dir(t_map *map, char spawn)
{
	if (spawn == 'N')
	{
		map->dir_x = 0.0;
		map->dir_y = -1.0;
	}
	else if (spawn == 'S')
	{
		map->dir_x = 0.0;
		map->dir_y = 1.0;
	}
	else if (spawn == 'E')
	{
		map->dir_x = 1.0;
		map->dir_y = 0.0;
	}
	else
	{
		map->dir_x = -1.0;
		map->dir_y = 0.0;
	}
}

static int	parse_player_position(t_map *map)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (is_spawn_char(map->grid[y][x]))
			{
				if (player_count > 0)
					return (printf("Error\nMultiple player positions\n"), ERROR);
				map->player_x = x + 0.5;
				map->player_y = y + 0.5;
				set_player_dir(map, map->grid[y][x]);
				player_count++;
			}
			x++;
		}
		y++;
	}
	if (player_count == 0)
		return (printf("Error\nNo player position found\n"), ERROR);
	return (0);
}

int	parse_cub_file(t_map *map, char *filename)
{
	int		fd;
	char	*line;
	int		config_count;
	int		map_started;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nCannot open file: %s\n", filename), ERROR);
	
	config_count = 0;
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_started && is_config_line(line))
		{
			if (parse_config_line(map, line) != 0)
				return (free(line), close(fd), ERROR);
			config_count++;
		}
		else if (is_map_line(line))
		{
			map_started = 1;
			if (add_map_line(map, line) != 0)
				return (free(line), close(fd), ERROR);
		}
		else if (map_started && line[0] == '\n')
		{
			// Empty line after map started - might be end of file
			// Check if next line is also empty or EOF
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	
	if (config_count != 6)
		return (printf("Error\nInvalid config (need NO,SO,WE,EA,F,C)\n"), ERROR);
	if (!map->grid)
		return (printf("Error\nNo map found in file\n"), ERROR);
	if (validate_map(map) != 0)
		return (ERROR);
	if (parse_player_position(map) != 0)
		return (ERROR);
	return (0);
}
