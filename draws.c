#include "cub3d.h"

void	draw_rectangle(t_game *game, int x, int y , int color)
{
	int i;
	int j;

	game->minimap_size = 10;
	x *= game->minimap_size;
	y *= game->minimap_size;
	i = 0;
	while (i < game->minimap_size - 1)
	{
		j = 0;
		while (j < game->minimap_size - 1)
		{
			game->img.data[(x + i) * game->width_screen + y + j] = color;
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
	while (i < game->map_size)
	{
		j = 0;
		while (j < ft_strlen(game->map[i]))
		{
			if (game->map[i][j] == '1')
				draw_rectangle(game, j, i , 0xFFFFFF);
			if (game->map[i][j] == '0')
				draw_rectangle(game, j, i, 0x33D1FF);
			if (game->map[i][j] == '2')
				draw_rectangle(game, j, i, 0xFA8800);
			draw_rectangle(game,game->posY + game->dirY * game->moveSpeed, game->posX + game->dirX * game->moveSpeed, 0xFF5733);
			j++;
		}
		i++;
	}
}