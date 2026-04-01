/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:59:03 by aramarak          #+#    #+#             */
/*   Updated: 2026/04/01 19:14:02 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error_outputs.h"

void	set_player_dir(t_map *map, char spawn)
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

int	parse_player_position(t_map *map)
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
