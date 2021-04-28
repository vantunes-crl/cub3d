#ifndef CUB3D_H
#define CUB3D_H

#include "mlx/mlx.h"
#include "key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define mapS 14
#define numSprites 19
#define uDiv 1
#define vDiv 1
#define vMove 0.0


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
	char *tex_south;
	char *tex_north;
	char *tex_east;
	char *tex_west;
	char *tex_sprite;
	int floor_color;
	int cell_color;
	int key_w;
	int key_s;
	int key_a;
	int key_d;
	int key_esc;
	int width_screen;
	int height_screen;
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void	*mlx;
	void	*win;
	t_img	img;
	int		buf[1024][1920];
	int		**texture;
	double zBuffer[1920];
	double	moveSpeed;
	double	rotSpeed;
	double sprite_posy;
	double sprite_posx;
	char 	**map1;
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

typedef struct s_sprite
{
	double 	y;
	double 	x;
	int 	texture;
	int		spriteOrder[numSprites];
    double	spriteDistance[numSprites];
	double spriteX;
	double spriteY;
	double invDet;
	double transformX;
	double transformY;
	int spriteScreenX;
	int vMoveScreen;
	int spriteHeight;
	int drawStartY;
	int drawEndY;
	int spriteWidth;
	int drawStartX;
	int drawEndX;
	int stripe;
	int d;
	int texX;
	int texY;
	int color;
	int j;
} t_sprite;

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

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
char	*ft_itoa(int n);
int		key_release(int key, t_game *game);
int		key_press(int key, t_game *game);
int		key_move(t_game *game);
void  	parse(t_game *game);
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
void 	parse_north(t_game *game, char *line, int i);
void 	parse_south(t_game *game, char *line, int i);
void 	parse_west(t_game *game, char *line, int i);
void 	parse_east(t_game *game, char *line , int i);
int		ft_isdigit(int c);
int		create_trgb(int r, int g, int b);
char	*ft_strdup(const char *s1);
int		ft_strlen(const char *str);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
void 	parse_map(t_game *game);

#endif