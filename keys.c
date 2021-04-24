#include "cub3d.h"

int	key_move(t_game *game)
{
	if (game->key_w)
	{
		if (!game->map[(int)(game->posX + game->dirX * game->moveSpeed)][(int)(game->posY)])
			game->posX += game->dirX * game->moveSpeed;
		if (!game->map[(int)(game->posX)][(int)(game->posY + game->dirY * game->moveSpeed)])
			game->posY += game->dirY * game->moveSpeed;
	}
	if (game->key_s)
	{
		if (!game->map[(int)(game->posX - game->dirX * game->moveSpeed)][(int)(game->posY)] || !game->map[(int)game->sprite_posx][(int)game->sprite_posy])
			game->posX -= game->dirX * game->moveSpeed;
		if (!game->map[(int)(game->posX)][(int)(game->posY - game->dirY * game->moveSpeed)] || !game->map[(int)game->sprite_posy][(int)game->sprite_posx])
			game->posY -= game->dirY * game->moveSpeed;
	}
	if (game->key_d)
	{
		double oldDirX = game->dirX;
		game->dirX = game->dirX * cos(-game->rotSpeed) - game->dirY * sin(-game->rotSpeed);
		game->dirY = oldDirX * sin(-game->rotSpeed) + game->dirY * cos(-game->rotSpeed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(-game->rotSpeed) - game->planeY * sin(-game->rotSpeed);
		game->planeY = oldPlaneX * sin(-game->rotSpeed) + game->planeY * cos(-game->rotSpeed);
	}

	if (game->key_a)
	{
		double oldDirX = game->dirX;
		game->dirX = game->dirX * cos(game->rotSpeed) - game->dirY * sin(game->rotSpeed);
		game->dirY = oldDirX * sin(game->rotSpeed) + game->dirY * cos(game->rotSpeed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(game->rotSpeed) - game->planeY * sin(game->rotSpeed);
		game->planeY = oldPlaneX * sin(game->rotSpeed) + game->planeY * cos(game->rotSpeed);
	}
	if (game->key_esc)
		exit(0);
	return (0);
}

int	key_press(int key, t_game *game)
{
	if (key == K_ESC)
	{
		mlx_destroy_window(game->mlx,game->win);
		exit(0);
	}
	else if (key == K_W)
		game->key_w = 1;
	else if (key == K_A)
		game->key_a = 1;
	else if (key == K_S)
		game->key_s = 1;
	else if (key == K_D)
		game->key_d = 1;
	return (0);
}

int		key_release(int key, t_game *game)
{
	if (key == K_ESC)
	{
		mlx_destroy_window(game->mlx,game->win);
		exit(0);
	}
	else if (key == K_W)
		game->key_w = 0;
	else if (key == K_A)
		game->key_a = 0;
	else if (key == K_S)
		game->key_s = 0;
	else if (key == K_D)
		game->key_d = 0;
	return (0);
}