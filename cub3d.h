#ifndef CUB3D_H
#define CUB3D_H

#include "mlx/mlx.h"
#include "key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define width 1024
#define height 512

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct	s_info
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void	*mlx;
	void	*win;
	t_img	img;
	int		buf[height][width];
	int		**texture;
	double	moveSpeed;
	double	rotSpeed;
    int     map[mapWidth][mapHeight];
}				t_info;

typedef struct s_flor
{
	float rayDirX0;
	float rayDirY0;
	float rayDirX1;
	float rayDirY1;
    int p;
    float posZ;
    float rowDistance;
    float floorStepX;
    float floorStepY;
    float floorY;
    float floorX;
    int y;
    double currentFloorX;
    double currentFloorY;
    int floorTexX; 
    int floorTexY;
    int checkerBoardPattern;

} t_flor;

typedef struct s_cell
{
	int x;
	int cellX;
	int cellY;
	int tx;
	int ty;
	int floorTexture;
	int ceilingTexture;
	int color;

} t_cell;

typedef struct s_wall
{
	double cameraX;
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	int x;
    int y;
	double sideDistX;
	double sideDistY;
	double perpWallDist;
	double deltaDistX;
	double deltaDistY;
	int stepX;
	int stepY;
	int hit;
	int side;
    int lineHeight;
    int drawStart;
    int drawEnd;
    double floorXWall; 
    double floorYWall;
    double weight;

} t_wall;

typedef struct s_textures
{
	int texX;
	int texNum;
	double wallX;
	double step;
	double texPos;
	int texY;
	int color;
    double distWall;
    double distPlayer;
    double currentDist;
    int floorTexture;
    int y;
} t_textures;

void    init_map(t_info *info);
void	draw(t_info *info);
t_flor put_flor(t_flor flor , t_info *info);
t_cell put_cell(t_info *info, t_flor *flor, t_cell cell);
void init_wall(t_wall *wall, t_info *info);
void steps(t_wall *wall , t_info *info);
void perp_wall(t_info *info, t_wall *wall);
int	key_press(int key, t_info *info);
void textures_wall(t_wall *wall, t_textures *textures, t_info *info);
void draw_wall(t_info *info, t_textures *textures, t_wall *wall);
void floor_wall(t_wall *wall, t_textures *textures);
void flor_wall2(t_info *info, t_textures *textures, t_wall *wall, t_flor *flor);
void	load_image(t_info *info, int *texture, char *path, t_img *img);
void	load_texture(t_info *info);

#endif