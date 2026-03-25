/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:13:47 by aramarak          #+#    #+#             */
/*   Updated: 2026/03/21 11:09:23 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Initializes and performs DDA raycasting for a given direction.
 *
 * @param d      Pointer to the main data structure.
 * @param dir_x  X component of the ray direction.
 * @param dir_y  Y component of the ray direction.
 * @param r      Pointer to the DDA ray structure (output).
 */
void	raycast_dda(t_data *d, double dir_x, double dir_y, t_dda *r)
{
	init_dda(d, dir_x, dir_y, r);
	cast_dda(d, r);
}
