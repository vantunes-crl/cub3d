CC			= gcc
CFLAGS		= -L mlx -lmlx -framework OpenGL -framework AppKit
RM			= rm -f

NAME		= cub3d.a
INCLUDE		= cub3d.h 

SRCS =	cub3d.c keys.c cub3d_utils.c draws.c init.c

all:
	$(CC) -L./mlx -lmlx -framework OpenGL -framework AppKit $(SRCS)
re:
	$(RM) a.out 
