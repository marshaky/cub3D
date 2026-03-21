/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_cast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 11:07:48 by aramarak          #+#    #+#             */
/*   Updated: 2026/03/21 11:07:48 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Checks if the cell at (mx, my) is a wall.
 * Returns 1 if the coordinates are out of bounds or if the cell is a wall,
 * 0 otherwise.
 *
 * @param m  Pointer to the map structure.
 * @param mx X coordinate in the map grid.
 * @param my Y coordinate in the map grid.
 * @return   1 if wall or out of bounds, 0 otherwise.
 */
static int	is_wall_cell(t_map *m, int mx, int my)
{
	if (mx < 0 || my < 0 || my >= m->height || mx >= m->width)
		return (1);
	return (m->grid[my][mx] == ICN_WALL);
}

/**
 * Performs the DDA (Digital Differential Analyzer) algorithm to cast a ray.
 * Advances the ray step by step until it hits a wall or reaches the maximum 
 * distance.
 *
 * @param d Pointer to the main data structure containing the map.
 * @param r Pointer to the DDA ray structure (holds ray state and result).
 * @return  void
 */
void	cast_dda(t_data *d, t_dda *r)
{
	while (r->dist < RAY_MAX_DIST)
	{
		if (r->side_x < r->side_y)
		{
			r->dist = r->side_x;
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->dist = r->side_y;
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (is_wall_cell(&d->map, r->map_x, r->map_y))
			break ;
	}
	if (r->dist > RAY_MAX_DIST)
		r->dist = RAY_MAX_DIST;
}
