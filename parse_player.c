#include "cub3d.h"

int	player_north(t_game *game, int j, int i)
{
	game->posY = j + 0.5;
	game->posX = i + 0.5;
	game->dirX = -1.0;
	game->dirY = 0.0;
	game->planeX = 0.0;
	game->planeY = 0.66;
	game->map[i][j] = '0';
	return (1);
}

int	player_south(t_game *game, int j, int i)
{
	game->posY = j + 0.5;
	game->posX = i + 0.5;
	game->dirX = 0.999767;
	game->dirY = -0.021591;
	game->planeX = -0.014250;
	game->planeY = -0.659846;
	game->map[i][j] = '0';
	return (1);
}

int	player_west(t_game *game, int j, int i)
{
	game->posY = j + 0.5;
	game->posX = i + 0.5;
	game->dirX = 0.029200;
	game->dirY = -0.999574;
	game->planeX = -0.659719;
	game->planeY = -0.019272;
	game->map[i][j] = '0';
	return (1);
}

int	player_east(t_game *game, int j, int i)
{
	game->posY = j + 0.5;
	game->posX = i + 0.5;
	game->dirX = 0.029200;
	game->dirY = 0.999573;
	game->planeX = 0.659718;
	game->planeY = -0.019272;
	game->map[i][j] = '0';
	return (1);
}

void	player_init(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	game->flag_player = 0;
	while (++i < game->map_size)
	{
		j = 0;
		while (j < ft_strlen(game->map[i]))
		{
			if (!check_all_map(game->map[i][j]))
				error(game, "No caracter map", 1);
			if (game->map[i][j] == 'N')
				game->flag_player += player_north(game, j, i);
			else if (game->map[i][j] == 'S')
				game->flag_player += player_south(game, j, i);
			else if (game->map[i][j] == 'W')
				game->flag_player += player_west(game, j, i);
			else if (game->map[i][j] == 'E')
				game->flag_player += player_east(game, j, i);
			j++;
		}
	}
	if (game->flag_player != 1)
		error(game, "More then one Player or no Player", 1);
}
