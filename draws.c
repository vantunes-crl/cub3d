#include "cub3d.h"

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
			my_mlx_pixel_put(game, x + i, y + j , color);
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
			else
				draw_rectangle(game, j, i, 0x000000);
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
	while (i++ < COLS)
		draw_line(game,i * mapS, 0, i * mapS, HEIGHT);
	j = 0;
	while (j++ < ROWS)
		draw_line(game, 0, j * mapS, WIDTH / 2, j * mapS);
}

void draw_player(t_game *game)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while(j++ < 8)
	{
		i = 0;
		while (i++ < 8)
			my_mlx_pixel_put(game, game->px + i, game->py + j, 0xF30808);
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
		my_mlx_pixel_put(game, fabs(x1), fabs(y1), 0xEE790A);
		x1 += deltaX;
		y1 += deltaY;
		i++;
	}
}