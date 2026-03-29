/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:20:32 by marshaky          #+#    #+#             */
/*   Updated: 2026/03/29 14:47:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error_outputs.h"

int	is_spawn_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_blank_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
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

static int	parse_before_map(t_map *map, char *line,
		int *config_count, int *map_started)
{
	if (is_blank_line(line))
		return (0);
	if (is_config_line(line))
	{
		if (parse_config_line(map, line) != 0)
			return (ERROR);
		(*config_count)++;
		return (0);
	}
	if (is_map_line(line))
	{
		*map_started = 1;
		if (add_map_line(map, line) != 0)
			return (ERROR);
		return (0);
	}
	return (printf(CONFIG_ERR), ERROR);
}

static int	parse_after_map(t_map *map, char *line)
{
	if (is_map_line(line))
		return (add_map_line(map, line));
	if (is_blank_line(line))
		return (printf(MAP_EMPTY_LINE_ERR), ERROR);
	return (printf(MAP_CHR_ERR), ERROR);
}

static int	read_cub_lines(int fd, t_map *map, int *config_count)
{
	char	*line;
	int		map_started;
	int		status;

	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_started)
			status = parse_before_map(map, line, config_count, &map_started);
		else
			status = parse_after_map(map, line);
		free(line);
		if (status != 0)
			return (ERROR);
		line = get_next_line(fd);
	}
	return (0);
}

static int	finalize_parse(t_map *map, int config_count)
{
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

int	parse_cub_file(t_map *map, char *filename)
{
	int	fd;
	int	config_count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf(OPEN_FILE_ERR, filename), ERROR);
	config_count = 0;
	if (read_cub_lines(fd, map, &config_count) != 0)
		return (close(fd), ERROR);
	close(fd);
	return (finalize_parse(map, config_count));
}
