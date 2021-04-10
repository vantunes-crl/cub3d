#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "mlx/mlx.h"
#include "string.h"

#define WIDTH 1024
#define HEIGHT 512
#define mapX 8
#define mapY 8

typedef struct s_img
{
    void *img;
    char *data;
    int endian;
    int bpp;
    int sizel;

} t_img;

typedef struct s_game
{
    void *mlx;
    void *win;
    t_img img;
    double posx; //positon of the player 
    double posy;
    double dir_x; // direction of player 
    double dix_y;
    double plane_x; // the camera plane of the player
    double plane_y;
    double movespeed;
    double rotspeed;
    int     map[mapX][mapY];

} t_game;

void    ft_mlx_pixel_put(t_game *game, int x, int y, int color);
void	map_init(t_game *game);
void    vertical_line(t_game *game, int x, int y1, int y2 , int color);


#endif