#include "cub3d.h"


t_flor put_flor(t_flor flor , t_info *info)
{
	flor.rayDirX0 = info->dirX - info->planeX;
	flor.rayDirY0 = info->dirY - info->planeY;
	flor.rayDirX1 = info->dirX + info->planeX;
	flor.rayDirY1 = info->dirY + info->planeY;
	flor.p = flor.y - height / 2;
	flor.posZ = 0.5 * height;
	flor.rowDistance = flor.posZ / flor.p;
	flor.floorStepX = flor.rowDistance * (flor.rayDirX1 - flor.rayDirX0) / width;
	flor.floorStepY = flor.rowDistance * (flor.rayDirY1 - flor.rayDirY0) / width;
	flor.floorX = info->posX + flor.rowDistance * flor.rayDirX0;
	flor.floorY = info->posY + flor.rowDistance * flor.rayDirY0;
	return(flor);
}

t_cell put_cell(t_info *info, t_flor *flor, t_cell cell)
{
	cell.cellX = (int)(flor->floorX);
	cell.cellY = (int)(flor->floorY);
	cell.tx = (int)(texWidth * (flor->floorX - cell.cellX)) & (texWidth - 1);
	cell.ty = (int)(texHeight * (flor->floorY - cell.cellY)) & (texHeight - 1);
	flor->floorX += flor->floorStepX;
	flor->floorY += flor->floorStepY;
	cell.floorTexture = 3;
	cell.ceilingTexture = 6;
	cell.color;
	cell.color = info->texture[cell.floorTexture][texWidth * cell.ty + cell.tx];
	cell.color = (cell.color >> 1) & 8355711;
	info->buf[flor->y][cell.x] = cell.color;
	cell.color = info->texture[cell.ceilingTexture][texWidth * cell.ty + cell.tx];
	cell.color = (cell.color >> 1) & 8355711;
	info->buf[height - flor->y - 1][cell.x] = cell.color;
	return (cell);
}

void init_wall(t_wall *wall, t_info *info)
{

	wall->cameraX = 2 * wall->x / (double)width - 1;
	wall->rayDirX = info->dirX + info->planeX * wall->cameraX;
	wall->rayDirY = info->dirY + info->planeY * wall->cameraX;
	wall->mapX = (int)info->posX;
	wall->mapY = (int)info->posY;
	wall->deltaDistX = fabs(1 / wall->rayDirX);
	wall->deltaDistY = fabs(1 / wall->rayDirY);
	wall->hit = 0;
}

void steps(t_wall *wall , t_info *info)
{
	if (wall->rayDirX < 0)
	{
		wall->stepX = -1;
		wall->sideDistX = (info->posX - wall->mapX) * wall->deltaDistX;
	}
	else
	{
		wall->stepX = 1;
		wall->sideDistX = (wall->mapX + 1.0 - info->posX) * wall->deltaDistX;
	}
	if (wall->rayDirY < 0)
	{
		wall->stepY = -1;
		wall->sideDistY = (info->posY - wall->mapY) * wall->deltaDistY;
	}
	else
	{
		wall->stepY = 1;
		wall->sideDistY = (wall->mapY + 1.0 - info->posY) * wall->deltaDistY;
	}

	while (wall->hit == 0)
	{
		if (wall->sideDistX < wall->sideDistY)
		{
			wall->sideDistX += wall->deltaDistX;
			wall->mapX += wall->stepX;
			wall->side = 0;
		}
		else
		{
			wall->sideDistY += wall->deltaDistY;
			wall->mapY += wall->stepY;
			wall->side = 1;
		}
		if (info->map[wall->mapX][wall->mapY] > 0) wall->hit = 1;
	}
}
void perp_wall(t_info *info, t_wall *wall)
{
	if (wall->side == 0)
		wall->perpWallDist = (wall->mapX - info->posX + (1 - wall->stepX) / 2) / wall->rayDirX;
	else
		wall->perpWallDist = (wall->mapY - info->posY + (1 - wall->stepY) / 2) / wall->rayDirY;
	wall->lineHeight = (int)(height / wall->perpWallDist);
	wall->drawStart = -wall->lineHeight / 2 + height / 2;
	if(wall->drawStart < 0)
		wall->drawStart = 0;
	wall->drawEnd = wall->lineHeight / 2 + height / 2;
	if(wall->drawEnd >= height)
		wall->drawEnd = height - 1;
}
