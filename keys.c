#include "cub3d.h"

int	key_press(int key, t_game *game)
{
	if (key == K_W)
	{
		if (!game->map[(int)(game->posX + game->dirX * game->moveSpeed)][(int)(game->posY)])
			game->posX += game->dirX * game->moveSpeed;
		if (!game->map[(int)(game->posX)][(int)(game->posY + game->dirY * game->moveSpeed)])
			game->posY += game->dirY * game->moveSpeed;
	}
	if (key == K_S)
	{
		if (!game->map[(int)(game->posX - game->dirX * game->moveSpeed)][(int)(game->posY)] || !game->map[(int)game->sprite_posx][(int)game->sprite_posy])
			game->posX -= game->dirX * game->moveSpeed;
		if (!game->map[(int)(game->posX)][(int)(game->posY - game->dirY * game->moveSpeed)] || !game->map[(int)game->sprite_posy][(int)game->sprite_posx])
			game->posY -= game->dirY * game->moveSpeed;
	}
	if (key == K_D)
	{
		double oldDirX = game->dirX;
		game->dirX = game->dirX * cos(-game->rotSpeed) - game->dirY * sin(-game->rotSpeed);
		game->dirY = oldDirX * sin(-game->rotSpeed) + game->dirY * cos(-game->rotSpeed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(-game->rotSpeed) - game->planeY * sin(-game->rotSpeed);
		game->planeY = oldPlaneX * sin(-game->rotSpeed) + game->planeY * cos(-game->rotSpeed);
	}

	if (key == K_A)
	{
		double oldDirX = game->dirX;
		game->dirX = game->dirX * cos(game->rotSpeed) - game->dirY * sin(game->rotSpeed);
		game->dirY = oldDirX * sin(game->rotSpeed) + game->dirY * cos(game->rotSpeed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(game->rotSpeed) - game->planeY * sin(game->rotSpeed);
		game->planeY = oldPlaneX * sin(game->rotSpeed) + game->planeY * cos(game->rotSpeed);
	}
	if (key == K_ESC)
		exit(0);
	return (0);
}
