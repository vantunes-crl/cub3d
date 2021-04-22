CC			= gcc
CFLAGS		= -L mlx -lmlx -framework OpenGL -framework AppKit
RM			= rm -f

NAME		= cub3d.a
INCLUDE		= cub3d.h 

SRCS =	cub3d.c calcs.c calcs2.c keys.c inits.c draws.c sprite.c itoa.c get_next_line.c get_next_line_utils.c parse.c atoi.c

all:
	$(CC) -lmlx -lm -framework OpenGL -framework AppKit $(SRCS)
re:
	$(RM) a.out 
