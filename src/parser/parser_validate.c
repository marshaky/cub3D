/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:22:01 by marshaky          #+#    #+#             */
/*   Updated: 2026/03/25 20:10:16 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error_outputs.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_walls_around(t_map *map, int y, int x)
{
	if (y == 0 || y == map->height - 1 || x == 0
		|| x == (int)ft_strlen(map->grid[y]) - 1)
	{
		if (map->grid[y][x] == '0' || is_spawn_char(map->grid[y][x]))
			return (ERROR);
	}
	if (map->grid[y][x] == '0' || is_spawn_char(map->grid[y][x]))
	{
		if (y > 0 && x < (int)ft_strlen(map->grid[y - 1]))
		{
			if (map->grid[y - 1][x] == ' ')
				return (ERROR);
		}
		if (y < map->height - 1 && x < (int)ft_strlen(map->grid[y + 1]))
		{
			if (map->grid[y + 1][x] == ' ')
				return (ERROR);
		}
		if (x > 0 && map->grid[y][x - 1] == ' ')
			return (ERROR);
		if (map->grid[y][x + 1] == ' ' || map->grid[y][x + 1] == '\0')
			return (ERROR);
	}
	return (0);
}

int	validate_map(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			// FIXME: FIX issue 
			if (!is_valid_char(map->grid[y][x]))
				return (printf(MAP_CHR_ERR), ERROR);
			if (check_walls_around(map, y, x) != 0)
				return (printf(MAP_WALL_ERR, y, x), ERROR);
			x++;
		}
		y++;
	}
	return (0);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
