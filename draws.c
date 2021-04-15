#include "cub3d.h"

void	draw_rectangle(t_game *game, int x, int y , int color)
{
	int i;
	int j;

	x *= mapS; // size of the cubes
	y *= mapS;
	i = 0;
	while (i < mapS - 1)
	{
		j = 0;
		while (j < mapS - 1)
		{
			game->img.data[(x + i) * width + y + j] = color;
			j++;
		}
		i++;
	}
}

void	draw_rectangle2(t_game *game, int x, int y , int color)
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
			game->img.data[(x + i) * width + y + j] = color;
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
	while (i < mapHeight)
	{
		j = 0;
		while (j < mapWidth)
		{
			if (game->map[i][j] >= 1)
				draw_rectangle(game, j, i , 0xFFFFFF);
			else
				draw_rectangle(game, j, i, 0x000000);
			draw_rectangle(game,floor(game->posX), floor(game->posY), 0xFFF400);
			j++;
		}
		i++;
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
		game->img.data[(int)fabs(x1) * width + (int)fabs(y1)] = 0xEE790A;
		x1 += deltaX;
		y1 += deltaY;
		i++;
	}
}