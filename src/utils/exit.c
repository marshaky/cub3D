/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:13:47 by aramarak          #+#    #+#             */
/*   Updated: 2026/03/04 14:16:16 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

static void	free_map_data(t_map *map)
{
	if (!map)
		return ;
	free_map_grid(map->grid);
	map->grid = NULL;
	free(map->tex_path_no);
	map->tex_path_no = NULL;
	free(map->tex_path_so);
	map->tex_path_so = NULL;
	free(map->tex_path_we);
	map->tex_path_we = NULL;
	free(map->tex_path_ea);
	map->tex_path_ea = NULL;
}

static void	destroy_graphics(t_data *d)
{
	int	i;

	if (!d || !d->mlx.mlx)
		return ;
	i = -1;
	while (++i < TEX_COUNT)
	{
		if (d->tex[i].img)
			mlx_destroy_image(d->mlx.mlx, d->tex[i].img);
		d->tex[i].img = NULL;
	}
	if (d->img.img)
		mlx_destroy_image(d->mlx.mlx, d->img.img);
	d->img.img = NULL;
	if (d->mlx.win)
		mlx_destroy_window(d->mlx.mlx, d->mlx.win);
	d->mlx.win = NULL;
	mlx_destroy_display(d->mlx.mlx);
	free(d->mlx.mlx);
	d->mlx.mlx = NULL;
}

void	free_data(t_data *d)
{
	if (!d)
		return ;
	free_map_data(&d->map);
	destroy_graphics(d);
}

int	clean_exit(t_data *d, int code)
{
	free_data(d);
	exit (code);
}
