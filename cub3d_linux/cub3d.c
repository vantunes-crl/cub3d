#include "include/mlx.h"
#include "cub3d.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

# define KEY_ESC		53
# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define EVENT_KEY_PRESS 2
# define EVENT_KEY_EXIT 17
# define ROWS 8
# define COLS 8
# define mapS 64
# define WIDTH 512
# define HEIGHT 512
# define PI 3.1415926535

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	float 	px;
	float	py;
	float	pdy; //player deltaX
	float	pdx; // player deltaY
	float	pa; // player ango
	int map[COLS][ROWS];
	void	*img;
	int	   *data;
	int		size_l;
	int		bpp;
	int		endian;

}				t_game;

void	draw_square(t_game *game, int size, int color , int posX , int posY) //funcao para formar uma quadrado de pixeis
{
	int		x;
	int		y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			mlx_pixel_put(game->mlx,game->win,posX + x, posY + y, color);
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
	int i;

	i = 0;

	deltaX = x2 - x1;
	deltaY = y2 - y1;
	if (fabs(deltaX) > fabs(deltaY))
		step = fabs(deltaX); 
	else
		step = fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (i <= step)
	{
		draw_square(game, 4, 0x444 ,fabs(x1), fabs(y1));
		x1 += deltaX;
		y1 += deltaY;
		i++;
	}
}

int key_press(int keycode, t_game *game) //move keys
{
	
	if (keycode == KEY_W)
	{
		game->px += game->pdx; //player receive deltaX
		game->py += game->pdy; //player receice deltaY
	}
	else if (keycode == KEY_S)
	{
		game->px += game->pdx;
		game->py += game->pdy;
	}
	else if (keycode == KEY_A)
	{
		game->pa-=0.1;
		if (game->pa < 0)
			game->pa+=2 * PI;
		game->pdx = cos(game->pa) * 20; 
		game->pdy = sin(game->pa) * 20;
	}
	else if (keycode == KEY_D)
	{
		game->pa+=0.1;
		if (game->pa > 2 * PI)
			game->pa-=2 * PI;
		game->pdx = cos(game->pa) * 20; 
		game->pdy = sin(game->pa) * 20;
	}
	return (0);
}

void img_init(t_game *game)
{
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = (int *)mlx_get_data_addr(game->img, &game->bpp, &game->size_l, &game->endian);
}
void	draw_rectangle(t_game *game, int x, int y , int color)
{
	int i;
	int j;

	x *= mapS; // size of the cubes
	y *= mapS;
	i = 0;
	while (i < mapS)
	{
		j = 0;
		while (j < mapS)
		{
			game->data[(y  + i) * WIDTH + x + j] = color;
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
				draw_rectangle(game, j, i , 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void draw_lines(t_game *game)
{
	int i;
	int j;

	i = 0;

	while (i < COLS)
	{
		draw_line(game,i * mapS, 0, i * mapS, HEIGHT);
		i++;
	}
	draw_line(game, COLS * mapS - 1, 0, COLS * mapS - 1, HEIGHT);
	j = 0;
	while (j < ROWS)
	{
		draw_line(game, 0, j * mapS, WIDTH, j * mapS);
		j++;
	}
	draw_line(game, 0, ROWS * mapS - 1, WIDTH, ROWS * mapS - 1);
}

void	game_init(t_game *game)
{	
	int map[ROWS][COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1},
	};
	memcpy(game->map, map, sizeof(int) * ROWS * COLS);
}

int		main_loop(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	draw_square(game, 10, 0xFFFFF, game->px , game->py); //player
	draw_rectangles(game);
	draw_line(game,game->pdx + game->px, game->pdy + game->py, game->px , game->py);
	draw_lines(game);
	return (0);
}

int main()
{
	t_game	game;

	game.px = HEIGHT / 2; //player incial position
	game.py = HEIGHT / 2; //player incial position
	game.pdx = cos(game.pa) * 20; //inicial player view
	game.pdy = sin(game.pa) * 20; 

	game_init(&game); // funcao que inicia o mapa
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3d"); //funcao que inicia a janela
	img_init(&game); //inicia a imagem
	mlx_hook(game.win, EVENT_KEY_PRESS, 1<<0L, &key_press, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);

	mlx_loop(game.mlx);
}