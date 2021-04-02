#include "cub3d.h"

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