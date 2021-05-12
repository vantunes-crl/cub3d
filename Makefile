CC	= gcc
MLX =  -lmlx -lm -framework OpenGL -framework AppKit
CFLAGS = -Wall -Werror -Wextra
RM			= rm -f

NAME		= cub3d.a
BONUS		= CUB3D.a
INCLUDE		= cub3d.h

SRCS = cub3d.c calcs.c calcs2.c keys.c inits.c draws.c sprite.c utils.c parse2.c get_next_line.c get_next_line_utils.c parse.c parse_player.c lst.c bmp.c utils2.c utils3.c parse3.c utils4.c

SRCS_BONUS = cub3d_bonus.c calcs_bonus.c calcs2.c keys.c inits.c draws.c sprite.c utils.c parse2.c get_next_line.c get_next_line_utils.c parse.c parse_player.c lst.c bmp.c utils2.c utils3.c parse3.c utils4.c

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(SRCS_BONUS:.c=.o)

$(BONUS) : $(BONUS_OBJS)
	gcc $(BONUS_OBJS) $(MLX) -o $(BONUS)

$(NAME) : $(OBJS)
	gcc  $(OBJS) $(MLX) -o $(NAME)

.c.o:
	gcc $(CFLAGS) -c $< -o $(<:.c=.o)

all : $(NAME)

clean :
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean : clean
	rm -rf $(NAME)
	rm -rf $(BONUS)
	rm -rf screenshot.bmp

re : fclean all

bonus : $(BONUS)