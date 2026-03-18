/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marshaky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:13:47 by aramarak          #+#    #+#             */
/*   Updated: 2026/03/18 13:37:10 by marshaky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	register_hooks(t_data *d)
{
	mlx_hook(d->mlx.win, EV_KEYDOWN, 1L << 0, on_keydown, d);
	mlx_hook(d->mlx.win, EV_KEYUP, 1L << 1, on_keyup, d);
	mlx_hook(d->mlx.win, EV_DESTROY, 0, on_destroy, d);
	mlx_loop_hook(d->mlx.mlx, render_frame, d);
}

static int	check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (ERROR);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (ERROR);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	d;

	if (argc != 2)
	{
		printf("Error\nUsage: %s <map.cub>\n", argv[0]);
		return (ERROR);
	}
	if (check_extension(argv[1]) != 0)
	{
		printf("Error\nInvalid file extension. Expected .cub\n");
		return (ERROR);
	}
	ft_memset(&d, 0, sizeof(d));
	if (app_init(&d) != 0)
		return (ERROR);
	if (parse_cub_file(&d.map, argv[1]) != 0)
		return (clean_exit(&d, ERROR));
	camera_init(&d.map);
	if (load_textures(&d) != 0)
		return (clean_exit(&d, ERROR));
	register_hooks(&d);
	mlx_loop(d.mlx.mlx);
	return (0);
}
