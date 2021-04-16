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
#define mapS 14
#define width 1920
#define height 1024

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

typedef struct	s_game
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
	double zBuffer[width];
	double	moveSpeed;
	double	rotSpeed;
    int     map[mapWidth][mapHeight];
}				t_game;

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
    int floorTexture;
    int y;
} t_textures;

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

void    init_map(t_game *game);
void	draw(t_game *game);
t_flor 	put_flor(t_flor flor , t_game *game);
t_cell 	put_cell(t_game *game, t_flor *flor, t_cell cell);
void 	init_wall(t_wall *wall, t_game *game);
void 	steps(t_wall *wall , t_game *game);
void 	perp_wall(t_game *game, t_wall *wall);
int		key_press(int key, t_game *game);
void 	textures_wall(t_wall *wall, t_textures *textures, t_game *game);
void 	draw_wall(t_game *game, t_textures *textures, t_wall *wall);
void	load_image(t_game *game, int *texture, char *path, t_img *img);
void	load_texture(t_game *game);
void	draw_rectangle(t_game *game, int x, int y , int color);
void	draw_rectangles(t_game *game);
void 	draw_lines(t_game *game);
void	draw_line(t_game *game, double x1, double y1, double x2, double y2);
void 	draw_sprites(t_game *game);
int		compare(const void *first, const void *second);
void	sort_order(t_pair *orders, int amount);
void	sortSprites(int *order, double *dist, int amount);

#endif