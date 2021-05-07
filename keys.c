#include "cub3d.h"

void key_up(t_game *game)
{
	if ((game->map[(int)(game->posX + game->dirX * game->moveSpeed)][(int)(game->posY)] == '0') || 
							(game->map[(int)(game->posX + game->dirX * game->moveSpeed)][(int)(game->posY)] == '2'))
		game->posX += game->dirX * game->moveSpeed;
	if ((game->map[(int)(game->posX)][(int)(game->posY + game->dirY * game->moveSpeed)] == '0') || 
							(game->map[(int)(game->posX)][(int)(game->posY + game->dirY * game->moveSpeed)] == '2'))
		game->posY += game->dirY * game->moveSpeed;
}

void key_down(t_game *game)
{
	if ((game->map[(int)(game->posX - game->dirX * game->moveSpeed)][(int)(game->posY)] == '0' || 
						game->map[(int)game->sprite_posx][(int)game->sprite_posy] == '0') || 
								(game->map[(int)(game->posX - game->dirX * game->moveSpeed)][(int)(game->posY)] == '0' ||
										 game->map[(int)game->sprite_posx][(int)game->sprite_posy] == '2'))
		game->posX -= game->dirX * game->moveSpeed;
	if ((game->map[(int)(game->posX)][(int)(game->posY - game->dirY * game->moveSpeed)] == '0' ||
						 game->map[(int)game->sprite_posy][(int)game->sprite_posx] == '0') ||
									 (game->map[(int)(game->posX)][(int)(game->posY - game->dirY * game->moveSpeed)] == '0' || 
														game->map[(int)game->sprite_posy][(int)game->sprite_posx] == '2'))
		game->posY -= game->dirY * game->moveSpeed;
}

void key_left(t_game *game)
{
		double oldDirX;
		double oldPlaneX;

		oldDirX = game->dirX;
		game->dirX = game->dirX * cos(-game->rotSpeed) - game->dirY * sin(-game->rotSpeed);
		game->dirY = oldDirX * sin(-game->rotSpeed) + game->dirY * cos(-game->rotSpeed);
		oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(-game->rotSpeed) - game->planeY * sin(-game->rotSpeed);
		game->planeY = oldPlaneX * sin(-game->rotSpeed) + game->planeY * cos(-game->rotSpeed);
}

void key_right(t_game *game)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = game->dirX;
	game->dirX = game->dirX * cos(game->rotSpeed) - game->dirY * sin(game->rotSpeed);
	game->dirY = oldDirX * sin(game->rotSpeed) + game->dirY * cos(game->rotSpeed);
	oldPlaneX = game->planeX;
	game->planeX = game->planeX * cos(game->rotSpeed) - game->planeY * sin(game->rotSpeed);
	game->planeY = oldPlaneX * sin(game->rotSpeed) + game->planeY * cos(game->rotSpeed);
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