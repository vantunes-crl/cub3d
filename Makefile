INCLIB=$(INC)/../lib

CC=gcc

CFLAGS= -I$(INC) -O3 -I..

NAME= cub3d.a
SRC = test.c 04_floor_ceiling.c calcs.c keys.c calcs2.c
OBJ = $(SRC:.c=.o)

all	:$(NAME)

$(NAME)	:$(OBJ)
	$(CC) -o $(NAME) $(OBJ) -L.. mlx_linux/libmlx_Linux.a -L$(INCLIB) -lXext -lX11 -lm -lbsd

clean	:
	rm -f $(NAME) $(OBJ) *~ core *.core


re	: clean all
