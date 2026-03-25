/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_query.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:13:47 by aramarak          #+#    #+#             */
/*   Updated: 2026/03/12 20:05:47 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Checks if the given (x, y) position is inside a wall or out of bounds.
 * Converts floating-point coordinates to integer grid indices and checks
 * the map cell.
 *
 * @param m Pointer to the map structure.
 * @param x X coordinate (double).
 * @param y Y coordinate (double).
 * @return  1 if wall or out of bounds, 0 otherwise.
 */
int	is_wall(t_map *m, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (mx < 0 || my < 0 || my >= m->height || mx >= m->width)
		return (1);
	return (m->grid[my][mx] == ICN_WALL);
}
