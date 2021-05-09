#include "cub3d.h"

void	key_up(t_game *game)
{
	int	posx;
	int	posy;

	posx = (int)(game->posX + game->dirX * game->moveSpeed);
	posy = (int)(game->posY + game->dirY * game->moveSpeed);
	if ((game->map[posx][(int)(game->posY)] == '0')
		|| (game->map[posx][(int)(game->posY)] == '2'))
		game->posX += game->dirX * game->moveSpeed;
	if ((game->map[(int)(game->posX)][posy] == '0')
		|| (game->map[(int)(game->posX)][posy] == '2'))
		game->posY += game->dirY * game->moveSpeed;
}

void	key_down(t_game *game)
{
	int	posx;
	int	posy;

	posx = (int)(game->posX - game->dirX * game->moveSpeed);
	posy = (int)(game->posY - game->dirY * game->moveSpeed);
	if ((game->map[posx][(int)(game->posY)] == '0'
		|| (game->map[posx][(int)(game->posY)] == '0')))
		game->posX -= game->dirX * game->moveSpeed;
	if ((game->map[(int)(game->posX)][posy] == '0'
		|| (game->map[(int)(game->posX)][posy] == '0')))
		game->posY -= game->dirY * game->moveSpeed;
}

void	key_left(t_game *game)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rt;

	rt = -game->rotSpeed;
	oldDirX = game->dirX;
	game->dirX = game->dirX * cos(rt) - game->dirY * sin(rt);
	game->dirY = oldDirX * sin(rt) + game->dirY * cos(rt);
	oldPlaneX = game->planeX;
	game->planeX = game->planeX * cos(rt) - game->planeY * sin(rt);
	game->planeY = oldPlaneX * sin(rt) + game->planeY * cos(rt);
}

void	key_right(t_game *game)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rt;

	rt = game->rotSpeed;
	oldDirX = game->dirX;
	game->dirX = game->dirX * cos(rt) - game->dirY * sin(rt);
	game->dirY = oldDirX * sin(rt) + game->dirY * cos(rt);
	oldPlaneX = game->planeX;
	game->planeX = game->planeX * cos(rt) - game->planeY * sin(rt);
	game->planeY = oldPlaneX * sin(rt) + game->planeY * cos(rt);
}

int	key_move(t_game *game)
{
	if (game->key_w)
		key_up(game);
	if (game->key_s)
		key_down(game);
	if (game->key_d)
		key_left(game);
	if (game->key_a)
		key_right(game);
	if (game->key_esc)
		exit(0);
	return (0);
}
