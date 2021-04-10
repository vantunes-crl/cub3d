#include "cub3d.h"

void	map_init(t_game *game)
{	
	int map[mapX][mapY] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1},
	};
	memcpy(game->map, map, sizeof(int) * mapX * mapY);
}

void ft_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char *dst;

    dst = game->img.data + (y * game->img.sizel + x * (game->img.bpp / 8));
    *(unsigned*) dst = color;
}

//imprime uma linha vertical x colunas , y1 e onde ela comeca e y2 onde ela termina 
void vertical_line(t_game *game, int x, int y1, int y2 , int color) 
{
    while (y1 < y2)
    {
        ft_mlx_pixel_put(game, x , y1 , color);
        y1++;
    }
}