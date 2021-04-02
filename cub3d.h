#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "mlx/mlx.h"

# define KEY_ESC		53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define EVENT_KEY_PRESS 2
# define EVENT_KEY_EXIT 17
# define ROWS 8
# define COLS 8
# define mapS 64
# define WIDTH 1024
# define HEIGHT 512
# define PI 3.1415926535

typedef struct	s_game
{
	void	*mlx;
	void	*win;
    void	*img;
	char	*data;
	float 	px;
	float	py;
	float	pdy; //player deltaX
	float	pdx; // player deltaY
	float	pa; // player ango
	int     map[COLS][ROWS];
	int		size_l;
	int		bpp;
	int		endian;

}				t_game;

void            draw_player(t_game *game);
int             key_press(int keycode, t_game *game);
void            my_mlx_pixel_put(t_game *data, int x, int y, int color);
void            draw_line(t_game *game, double x1, double y1, double x2, double y2);
void            img_init(t_game *game);
void	        draw_rectangle(t_game *game, int x, int y , int color);
void	        draw_rectangles(t_game *game);
void            draw_lines(t_game *game);
void	        map_init(t_game *game);


#endif