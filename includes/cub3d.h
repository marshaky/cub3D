/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:14:38 by aramarak          #+#    #+#             */
/*   Updated: 2026/04/17 19:50:47 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "../libraries/libft/libft.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line.h"

/* ************************************************************************** */
/*                                                                            */
/*                               main defines                                 */
/*                                                                            */
/* ************************************************************************** */
# define ERROR					1
# ifdef __linux__1
#  define WINDOW_WIDTH			2560
#  define WINDOW_HEIGHT			1440
# else
#  define WINDOW_WIDTH			1280
#  define WINDOW_HEIGHT			720
# endif
# define RAY_STEP				0.02
# define RAY_MAX_DIST			200.0
# define PI						3.14159265358979323846
# define DEG_TO_RAD				0.017453292519943295
# define SCENE_FOV				66.0
# define MOVE_SPEED				0.04
# define ROT_SPEED				0.02
/* ************************************************************************** */
/*                            minimap variables                               */
/* ************************************************************************** */
# define MINIMAP_TILE			64
# define MINIMAP_PLAYER_SIZE	32
# define MINIMAP_X				10
# define MINIMAP_Y				10
# define MINIMAP_FOV 			66.0
# define MINIMAP_RAYS 			66
/* ************************************************************************** */
/*                               map types                                    */
/* ************************************************************************** */
# define ICN_WALL				'1'
# define ICN_GROUND				'0'
# define ICN_PLAYER				'N'
/* ************************************************************************** */
/*                               map colors                                   */
/* ************************************************************************** */
# define MAP_COLOR_WALL			0x00FFFFFF
# define MAP_COLOR_ELSE			0x00333333
# define MAP_COLOR_GRID			0x00555555
# define MAP_COLOR_PLYR			0x00FF0000
# define MAP_COLOR_PLDR			0x00FFFF00
# define MAP_COLOR_RYCT			0x0000FF00
/* ************************************************************************** */
/*                             scene colors                                   */
/* ************************************************************************** */
# define CEILING_COLOR			0x0087CEEB
# define FLOOR_COLOR			0x00999999
# define WALL_NORTH_COLOR		0x00FF9999
# define WALL_SOUTH_COLOR		0x0099FF99
# define WALL_EAST_COLOR		0x009999FF
# define WALL_WEST_COLOR		0x00FFFF99
/* ************************************************************************** */
/*                               keycodes Linux                               */
/* ************************************************************************** */
# ifdef __linux__
#  define KEY_ESC				65307
#  define EV_KEYDOWN			2
#  define EV_KEYUP				3
#  define EV_DESTROY			17
#  define KEY_A					97
#  define KEY_D					100
#  define KEY_W					119
#  define KEY_S					115
#  define KEY_AR_L				65361
#  define KEY_AR_R				65363
#  define KEY_AR_T				65362
#  define KEY_AR_B				65364
# else
#  define KEY_ESC				53
#  define EV_KEYDOWN			2
#  define EV_KEYUP				3
#  define EV_DESTROY			17
#  define KEY_A					0
#  define KEY_D					2
#  define KEY_W					13
#  define KEY_S					1
#  define KEY_AR_L				123
#  define KEY_AR_R				124
#  define KEY_AR_T				126
#  define KEY_AR_B				125
# endif
/* ************************************************************************** */
/*                               structures                                   */
/* ************************************************************************** */
typedef struct s_wall_column
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;
}	t_wall_column;

typedef struct s_move
{
	int		forward;
	int		backward;
	int		strafe_left;
	int		strafe_right;
	int		turn_left;
	int		turn_right;
}	t_move;

typedef struct s_dda
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	double	dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
}	t_dda;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		w;
	int		h;
}	t_mlx;

typedef struct s_img
{
	void	*img;
	char	*addr;

	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_tex
{
	void	*img;
	char	*addr;

	int		width;
	int		height;

	int		bpp;
	int		line_len;
	int		endian;
}	t_tex;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;

	double	player_x;
	double	player_y;

	double	dir_x;
	double	dir_y;

	double	plane_x;
	double	plane_y;

	int		floor_color;
	int		ceil_color;

	char	*tex_path_no;
	char	*tex_path_so;
	char	*tex_path_we;
	char	*tex_path_ea;
}	t_map;

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	color;
}	t_line;

enum e_tex
{
	TEX_NO = 0,
	TEX_SO = 1,
	TEX_WE = 2,
	TEX_EA = 3,
	TEX_COUNT = 4
};

typedef struct s_data
{
	t_mlx	mlx;
	t_img	img;
	t_map	map;
	t_tex	tex[TEX_COUNT];

	int		exit_code;
	t_move	move;
}	t_data;

typedef struct s_render_ctx
{
	t_data			*d;
	t_wall_column	*col;
	t_dda			*r;
	t_tex			*t;
	int				x;
	int				*y;
	// temp values
	double			wall_x;
	int				tex_x;
	int				tex_y;
	int				color;
	double			step;
	double			tex_pos;
}	t_render_ctx;

typedef struct s_parse_player_pos
{
	int				x;
	int				y;
	int				player_count;
}	t_parse_player_pos;

typedef struct s_add_map_line_tmp
{
	int				i;
	int				len;
	char			*trimmed;
	char			**new_grid;
}	t_add_map_line_tmp;

/* ************************************************************************** */
/*                                                                            */
/*                               cub3d API                                    */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*     src/engine/raycast     raycast_dda .c                                  */
/* ************************************************************************** */
void			raycast_dda(t_data *d, double dir_x, double dir_y, t_dda *r);

/* ************************************************************************** */
/*     src/engine/raycast     raycast_cast .c                                 */
/* ************************************************************************** */
void			cast_dda(t_data *d, t_dda *r);

/* ************************************************************************** */
/*     src/engine/raycast     raycast_init .c                                 */
/* ************************************************************************** */
void			init_dda(t_data *d, double dir_x, double dir_y, t_dda *r);

/* ************************************************************************** */
/*     src/hooks              hooks .c                                        */
/* ************************************************************************** */
int				on_keydown(int keycode, void *param);
int				on_keyup(int keycode, void *param);
int				on_destroy(void *param);

/* ************************************************************************** */
/*     src/init              init.c                                           */
/* ************************************************************************** */
int				data_init(t_data *d);
int				graphics_init(t_data *d);
void			camera_init(t_map *map);

/* ************************************************************************** */
/*     src/loader            init.c                                           */
/* ************************************************************************** */
int				load_textures(t_data *d);
int				load_texture(t_data *d, t_tex *tex, char *path);

/* ************************************************************************** */
/*     src/map                  map_query.c                                   */
/* ************************************************************************** */
int				is_wall(t_map *m, double x, double y);

/* ************************************************************************** */
/*     src/player            player_move.c                                    */
/* ************************************************************************** */
void			player_move_forward(t_data *d);
void			player_move_backward(t_data *d);
void			player_strafe_left(t_data *d);
void			player_strafe_right(t_data *d);

/* ************************************************************************** */
/*     src/player            player_rotate.c                                  */
/* ************************************************************************** */
void			player_rotate(t_data *d, double angle);

/* ************************************************************************** */
/*     src/player            player_update.c                                  */
/* ************************************************************************** */
void			player_update(t_data *d);

/* ************************************************************************** */
/*     src/render         render_column_utils.c                               */
/* ************************************************************************** */
void			draw_ceiling(t_data *d, int x, int *y, int draw_start);
void			draw_floor(t_data *d, int x, int y);
void			draw_flat_wall(t_data *d, int x, int *y, t_wall_column *col);
void			draw_textured_wall(t_render_ctx *ctx);

/* ************************************************************************** */
/*     src/render         render_scene.c                                      */
/* ************************************************************************** */
void			render_scene(t_data *d);

/* ************************************************************************** */
/*     src/render         render_utils.c                                      */
/* ************************************************************************** */
unsigned int	texel_at(t_tex *t, int x, int y);
int				pick_tex_id(t_dda *r);

/* ************************************************************************** */
/*     src/render         render_walls.c                                      */
/* ************************************************************************** */
void			render_wall_column(t_data *d, int x);
void			draw_wall_column(t_data *d, int x, t_dda *r);
void			draw_column_pixels(t_data *d, int x, t_wall_column *col,
					t_dda *r);
double			compute_wall_x(t_dda *r);

/* ************************************************************************** */
/*     src/render               render.c                                      */
/* ************************************************************************** */
void			ft_put_pixel(t_img *img, int x, int y, int color);
int				render_frame(void *param);

/* ************************************************************************** */
/*     src/render/minimap      minimap_player_pos.c                           */
/* ************************************************************************** */
void			get_player_minimap_pos(t_data *d, int *x, int *y);

/* ************************************************************************** */
/*     src/render/minimap      minimap_utils.c                                */
/* ************************************************************************** */
void			draw_square(t_data *d, int x, int y, int color);
void			draw_tile_with_border(t_data *d, int x, int y, int fill_color);

/* ************************************************************************** */
/*     src/render/minimap      minimap.c                                      */
/* ************************************************************************** */
void			draw_minimap(t_data *d);
void			draw_map_tiles(t_data *d);
void			draw_player_minimap(t_data *d);
void			draw_player_direction(t_data *d);
void			draw_line(t_data *d, t_line l);

/* ************************************************************************** */
/*     src/render/minimap      minimap_ray.c                                  */
/* ************************************************************************** */
void			draw_minimap_rays(t_data *d);

/* ************************************************************************** */
/*     src/utils                    exit.c                                    */
/* ************************************************************************** */
int				clean_exit(t_data *d, int code);

/* ************************************************************************** */
/*     src/utils                 helpers.c                                    */
/* ************************************************************************** */
int				ft_isspace(int c);
int				ft_arrlen(char **arr);
int				is_str_digit(char *s);

/* ************************************************************************** */
/*     src/parser            parser_player.c                                  */
/* ************************************************************************** */
void			set_player_dir(t_map *map, char spawn);
int				parse_player_position(t_map *map);

/* ************************************************************************** */
/*     src/parser            parser_checkers.c                                */
/* ************************************************************************** */
int				is_spawn_char(char c);
int				is_blank_line(char *line);

/* ************************************************************************** */
/*     src/parser            parser.c                                         */
/* ************************************************************************** */
int				parse_cub_file(t_map *map, char *filename);

/* ************************************************************************** */
/*     src/parser            parser_utils.c                                   */
/* ************************************************************************** */
int				is_config_line(char *line);
int				is_map_line(char *line);
int				parse_config_line(t_map *map, char *line);
int				add_map_line(t_map *map, char *line);
void			free_split(char **arr);

/* ************************************************************************** */
/*     src/parser            parser_validate.c                                */
/* ************************************************************************** */
int				validate_map(t_map *map);

#endif	//CUB3D_H
