#include "mlx/mlx.h"
#include "cub3d.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

# define KEY_ESC		53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define EVENT_KEY_PRESS 2
# define EVENT_KEY_EXIT 17
# define TILE_SIZE 80
# define ROWS 11
# define COLS 15
# define WIDTH COLS * TILE_SIZE
# define HEIGHT ROWS * TILE_SIZE
# define TO_COORD(X, Y) ((int)floor(Y) * WIDTH + (int)floor(X))
# define PI 3.1415926535

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
}				t_img;

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	t_img	img;
	float 	x;
	float	y;
	int		map[ROWS][COLS];
	float	pdy; //player deltaX
	float	pdx; // player deltaY
	float	pa; // player ango

}				t_game;


void	draw_square(t_game *game, int size, int color) //funcao para formar uma quadrado de pixeis
{
	int		x;
	int		y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			mlx_pixel_put(game->mlx, game->win, x + game->x, y + game->y, color);
			x++;
		}
		y++;
	}
}

void draw_line(t_game *game, double x1, double y1, double x2, double y2)
{
	double deltaX;
	double deltaY;
	double step;

	deltaX = x2 - x1;
	deltaY = y2 - y1;
	if (fabs(deltaX) > fabs(deltaY))
		step = fabs(deltaX); 
	else
		step = fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
	{
		game->img.data[TO_COORD(x1, y1)] = 0xb3b3b3;
		x1 += deltaX;
		y1 += deltaY;
	}
}

void draw_lines(t_game *game)
{
	int i;
	int j;

	i = 0;

	while (i < COLS)
	{
		draw_line(game,i * TILE_SIZE, 0, i * TILE_SIZE, HEIGHT);
		i++;
	}
	draw_line(game, COLS * TILE_SIZE - 1, 0, COLS * TILE_SIZE - 1, HEIGHT);
	j = 0;
	while (j < ROWS)
	{
		draw_line(game, 0, j * TILE_SIZE, WIDTH, j * TILE_SIZE);
		j++;
	}
	draw_line(game, 0, ROWS * TILE_SIZE - 1, WIDTH, ROWS * TILE_SIZE - 1);
}

int key_press(int keycode, t_game *game) //move keys
{
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_W)
	{
		game->x += game->pdx; //player receive deltaX
		game->y += game->pdy; //player receice deltaY
	}
	else if (keycode == KEY_S)
	{
		game->x += game->pdx;
		game->y += game->pdy;
	}
	else if (keycode == KEY_A)
	{
		game->pa-=0.1;
		if (game->pa < 0)
			game->pa+=2 * PI;
		game->pdx = cos(game->pa) * 5; 
		game->pdy = sin(game->pa) * 5;
	}
	else if (keycode == KEY_D)
	{
		game->pa+=0.1;
		if (game->pa > 2 * PI)
			game->pa-=2 * PI;
		game->pdx = cos(game->pa) * 5; 
		game->pdy = sin(game->pa) * 5;
	}
	return (0);
}

void	draw_rectangle(t_game *game, int x, int y)
{
	int i;
	int j;

	x *= TILE_SIZE; // size of the cubes
	y *= TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			game->img.data[(y  + i) * WIDTH + x + j] = 0xFFFFFF;
			j++;
		}
		i++;
	}
}

void	draw_rectangles(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			if (game->map[i][j] == 1)
				draw_rectangle(game, j, i);
			j++;
		}
		i++;
	}
}

int close(t_game *game)
{
	exit(0);
}

void img_init(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.data = (int *)mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.size_l, &game->img.endian);
}

void	window_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
}

void	game_init(t_game *game)
{	
	int map[ROWS][COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	memcpy(game->map, map, sizeof(int) * ROWS * COLS);
}

int		main_loop(t_game *game)
{

	draw_rectangles(game);
	draw_lines(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	draw_square(game, 20, 0xb3b3b4); //player
	mlx_pixel_put(game->mlx,game->win, game->x+game->pdx*5, game->y+game->pdy*5,0xb3b3b4 );
	return (0);
}
// void draw_rays(t_game *game)
// {
// 	int r,mx,my,mp,dof;
// 	float rx,ry,ra,xo,yo;
// 	ra = game->pa;
// 	for (r = 0; r < 1; r++)
// 	{
// 		dof = 0;
// 		float aTan=-1/tan(ra);
// 		if (ra > PI) //loooking right
// 		{
// 			ry = (((int)game->y>>6)<<6)-0.0001; 
// 			rx = game->y - ry * aTan + game->x;
// 			yo=-64;
// 			xo=-yo * aTan;
// 		}
// 		if (ra < PI) //looking left
// 		{
// 			ry = (((int)game->y>>6)<<6) + 64; 
// 			rx = (game->y - ry) * aTan + game->x;
// 			yo = 64;
// 			xo=-yo * aTan;
// 		}
// 		if (ra==0 || ra==PI) //looking straight
// 		{
// 			rx = game->x;
// 			ry = game->y;
// 			dof = 8;
// 		}
// 		while (dof < 8)
// 		{
// 			mx = (int)(rx)>>6;
// 			my = (int)(ry)>>6;
// 			mp = my * ROWS + mx;
// 			if (mp < ROWS * COLS && game->map[0][mp] == 1)
// 				dof = 8;
// 			else
// 			{
// 				rx += xo;
// 				ry += yo;
// 				dof += 1;
// 			}
// 		}
// 	}
// }

int main()
{
	t_game	game;

	game.x = HEIGHT / 2; //player incial position
	game.y = HEIGHT / 2; //player incial position
	game.pdx = cos(game.pa) * 5; //inicial player view
	game.pdy = sin(game.pa) * 5; 

	game_init(&game); // funcao que inicia o mapa
	window_init(&game); //funcao que inicia a janela
	img_init(&game); //inicia a imagem
	mlx_hook(game.win, EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_hook(game.win, EVENT_KEY_EXIT, 0, &close, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);

	mlx_loop(game.mlx);
}