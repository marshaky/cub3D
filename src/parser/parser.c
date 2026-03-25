/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:20:32 by marshaky          #+#    #+#             */
/*   Updated: 2026/03/25 20:12:35 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error_outputs.h"

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
	t_parse_player_pos	tmp;

	tmp.player_count = 0;
	tmp.y = 0;
	while (map->grid[tmp.y])
	{
		tmp.x = 0;
		while (map->grid[tmp.y][tmp.x])
		{
			if (is_spawn_char(map->grid[tmp.y][tmp.x]))
			{
				if (tmp.player_count > 0)
					return (printf(MUL_PLAYER_POS), ERROR);
				map->player_x = tmp.x + 0.5;
				map->player_y = tmp.y + 0.5;
				set_player_dir(map, map->grid[tmp.y][tmp.x]);
				tmp.player_count++;
			}
			tmp.x++;
		}
		tmp.y++;
	}
	if (tmp.player_count == 0)
		return (printf(NO_PLAYER_POS), ERROR);
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
		return (printf(OPEN_FILE_ERR, filename), ERROR);
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
			// FIXME: put actual comments afterm map
			printf("My dubby error");
			return (free(line), close(fd), ERROR);
		}
		else
		{
			// FIXME: put actual comments invalid character
			printf(CONFIG_ERR);
			return (free(line), close(fd), ERROR);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (config_count != 6)
		return (printf(CONFIG_ERR), ERROR);
	if (!map->grid)
		return (printf(MAP_FIND_ERR), ERROR);
	if (validate_map(map) != 0)
		return (ERROR);
	if (parse_player_position(map) != 0)
		return (ERROR);
	return (0);
}
