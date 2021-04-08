#include "cub3d.h"

int	key_press(int key, t_info *info)
{
	if (key == K_W)
	{
		if (!info->map[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->dirX * info->moveSpeed;
		if (!info->map[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)])
			info->posY += info->dirY * info->moveSpeed;
	}
	if (key == K_S)
	{
		if (!info->map[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->dirX * info->moveSpeed;
		if (!info->map[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
			info->posY -= info->dirY * info->moveSpeed;
	}
	if (key == K_D)
	{

		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}

	if (key == K_A)
	{
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	if (key == K_ESC)
		exit(0);
	return (0);
}
