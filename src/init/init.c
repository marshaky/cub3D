/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:13:47 by aramarak          #+#    #+#             */
/*   Updated: 2026/03/04 14:12:21 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Initializes the camera plane for the player based on their direction.
 * Calculates the camera plane vector (perpendicular to the direction vector)
 * using the field of view (FOV).
 *
 * @param map Pointer to the map structure containing player direction and plane.
 * @return    void
 */
void	camera_init(t_map *map)
{
	double	plane_len;

	plane_len = tan((SCENE_FOV * DEG_TO_RAD) / 2.0);
	map->plane_x = -map->dir_y * plane_len;
	map->plane_y = map->dir_x * plane_len;
}

/**
 * Initializes the application window, image buffer, and camera plane.
 * Sets up the MLX window, image, and retrieves the image data address.
 * Returns ERROR if any initialization step fails.
 *
 * @param d Pointer to the main data structure (t_data).
 * @return  0 on success, ERROR on failure.
 */
int	app_init(t_data *d)
{
	d->mlx.w = WINDOW_WIDTH;
	d->mlx.h = WINDOW_HEIGHT;
	d->mlx.mlx = mlx_init();
	if (!d->mlx.mlx)
		return (ERROR);
	d->mlx.win = mlx_new_window(d->mlx.mlx, d->mlx.w, d->mlx.h, "cub3d");
	if (!d->mlx.win)
		return (ERROR);
	d->img.img = mlx_new_image(d->mlx.mlx, d->mlx.w, d->mlx.h);
	if (!d->img.img)
		return (ERROR);
	d->img.addr = mlx_get_data_addr(d->img.img, &d->img.bpp,
			&d->img.line_len, &d->img.endian);
	if (!d->img.addr)
		return (ERROR);
	camera_init(&d->map);
	return (0);
}
