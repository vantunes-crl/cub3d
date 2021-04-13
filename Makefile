CC			= gcc
CFLAGS		= -L mlx -lmlx -framework OpenGL -framework AppKit -g
RM			= rm -f

NAME		= cub3d.a
INCLUDE		= cub3d.h 

SRCS =	cub3d.c calcs.c calcs2.c keys.c test.c

all:
	$(CC) -lmlx -lm -framework OpenGL -framework AppKit -g $(SRCS)
re:
	$(RM) a.out 
