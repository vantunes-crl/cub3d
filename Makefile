CC	= gcc
MLX =  -lmlx -lm -framework OpenGL -framework AppKit
CFLAGS = 
RM			= rm -f

NAME		= cub3d.a
INCLUDE		= cub3d.h

SRCS = cub3d.c calcs.c calcs2.c keys.c inits.c draws.c sprite.c utils.c parse2.c get_next_line.c get_next_line_utils.c parse.c parse_player.c lst.c bmp.c utils2.c utils3.c parse3.c utils4.c

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	gcc  $(OBJS) $(MLX) -o $(NAME)

.c.o:
	gcc $(CFLAGS) -c $< -o $(<:.c=.o)

all : $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)
	rm -rf screenshot.bmp

re : fclean all

bonus : $(NAME)