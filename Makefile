NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR      = src

ENGINE_DIR   = $(SRC_DIR)/engine
RAYCAST_DIR  = $(ENGINE_DIR)/raycast

HOOK_DIR     = $(SRC_DIR)/hooks
INIT_DIR     = $(SRC_DIR)/init
MAP_DIR      = $(SRC_DIR)/map
PLAYER_DIR   = $(SRC_DIR)/player
PARSER_DIR   = $(SRC_DIR)/parser
SRC_GNL		 = $(SRC_DIR)/gnl

RENDER_DIR   = $(SRC_DIR)/render
MINIMAP_DIR  = $(RENDER_DIR)/minimap

UTILS_DIR    = $(SRC_DIR)/utils
LOADER_DIR   = $(SRC_DIR)/loader

SRC = \
	$(RAYCAST_DIR)/raycast_cast.c \
	$(RAYCAST_DIR)/raycast_dda.c \
	$(RAYCAST_DIR)/raycast_init.c \
	$(SRC_GNL)/get_next_line_utils.c \
	$(SRC_GNL)/get_next_line.c \
	$(HOOK_DIR)/hooks.c \
	$(INIT_DIR)/init.c \
	$(LOADER_DIR)/loader.c \
	$(PARSER_DIR)/parser.c \
	$(PARSER_DIR)/parser_checkers.c \
	$(PARSER_DIR)/parser_color.c \
	$(PARSER_DIR)/parser_player.c \
	$(PARSER_DIR)/parser_utils.c \
	$(PARSER_DIR)/parser_validate.c \
	$(MAP_DIR)/map_query.c \
	$(PLAYER_DIR)/player_move.c \
	$(PLAYER_DIR)/player_update.c \
	$(PLAYER_DIR)/player_rotate.c \
	$(MINIMAP_DIR)/minimap_player_pos.c \
	$(MINIMAP_DIR)/minimap_ray.c \
	$(MINIMAP_DIR)/minimap_utils.c \
	$(MINIMAP_DIR)/minimap_line.c \
	$(MINIMAP_DIR)/minimap.c \
	$(RENDER_DIR)/render_column_utils.c \
	$(RENDER_DIR)/render_scene.c \
	$(RENDER_DIR)/render_utils.c \
	$(RENDER_DIR)/render_walls.c \
	$(RENDER_DIR)/render.c \
	$(UTILS_DIR)/helpers.c \
	$(UTILS_DIR)/exit.c \
	$(SRC_DIR)/main.c

OBJS			=	$(SRC:.c=.o)

HEADER 			= 	includes/cub3d.h
INCS			=	-Iincludes -I$(MINILIBX)

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g
RM				=	rm -rf

LIBFT_PATH		=	libraries/libft
LIBFT			=	$(LIBFT_PATH)/libft.a

ifeq ($(shell uname -s), Linux)
	MINILIBX	=	libraries/minilibx-linux
	MLX_FLAGS	=	-L $(MINILIBX) -lmlx -lm -lX11 -lXext
else
	MINILIBX    =	libraries/minilibx-macos
	MLX_FLAGS   =	-L $(MINILIBX) -framework OpenGL -framework AppKit -lmlx -lm
endif

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

all: mlx libft $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

mlx:
	$(MAKE) -C $(MINILIBX)

libft:
	$(MAKE) -C $(LIBFT_PATH)

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(MINILIBX)
	$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re libft mlx
