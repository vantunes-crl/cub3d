CC			= gcc
CFLAGS		= -L mlx -lmlx -framework OpenGL -framework AppKit
RM			= rm -f

NAME		= cub3d.a
INCLUDE		= cub3d.h 

SRCS =	main.c utils.c

all:
	$(CC) -L./mlx -lmlx -framework OpenGL -framework AppKit $(SRCS)
re:
	$(RM) a.out 
