#include "cub3d.h"


t_flor put_flor(t_flor flor , t_game *game)
{
	flor.rayDirX0 = game->dirX - game->planeX;
	flor.rayDirY0 = game->dirY - game->planeY;
	flor.rayDirX1 = game->dirX + game->planeX;
	flor.rayDirY1 = game->dirY + game->planeY;
	flor.p = flor.y - height / 2;
	flor.posZ = 0.5 * height;
	flor.rowDistance = flor.posZ / flor.p;
	flor.floorStepX = flor.rowDistance * (flor.rayDirX1 - flor.rayDirX0) / width;
	flor.floorStepY = flor.rowDistance * (flor.rayDirY1 - flor.rayDirY0) / width;
	flor.floorX = game->posX + flor.rowDistance * flor.rayDirX0;
	flor.floorY = game->posY + flor.rowDistance * flor.rayDirY0;
	return(flor);
}

t_cell put_cell(t_game *game, t_flor *flor, t_cell cell)
{
	cell.cellX = (int)(flor->floorX);
	cell.cellY = (int)(flor->floorY);
	cell.tx = (int)(texWidth * (flor->floorX - cell.cellX)) & (texWidth - 1);
	cell.ty = (int)(texHeight * (flor->floorY - cell.cellY)) & (texHeight - 1);
	flor->floorX += flor->floorStepX;
	flor->floorY += flor->floorStepY;
	cell.color = game->floor_color;
	cell.color = (cell.color >> 1) & 8355711;
	game->buf[flor->y][cell.x] = cell.color;
	cell.color = game->cell_color;
	cell.color = (cell.color >> 1) & 8355711;
	game->buf[height - flor->y - 1][cell.x] = cell.color;
	return (cell);
}

void init_wall(t_wall *wall, t_game *game)
{

	wall->cameraX = 2 * wall->x / (double)width - 1;
	wall->rayDirX = game->dirX + game->planeX * wall->cameraX;
	wall->rayDirY = game->dirY + game->planeY * wall->cameraX;
	wall->mapX = (int)game->posX;
	wall->mapY = (int)game->posY;
	wall->deltaDistX = fabs(1 / wall->rayDirX);
	wall->deltaDistY = fabs(1 / wall->rayDirY);
	wall->hit = 0;
}

void steps(t_wall *wall , t_game *game)
{
	if (wall->rayDirX < 0)
	{
		wall->stepX = -1;
		wall->sideDistX = (game->posX - wall->mapX) * wall->deltaDistX;
	}
	else
	{
		wall->stepX = 1;
		wall->sideDistX = (wall->mapX + 1.0 - game->posX) * wall->deltaDistX;
	}
	if (wall->rayDirY < 0)
	{
		wall->stepY = -1;
		wall->sideDistY = (game->posY - wall->mapY) * wall->deltaDistY;
	}
	else
	{
		wall->stepY = 1;
		wall->sideDistY = (wall->mapY + 1.0 - game->posY) * wall->deltaDistY;
	}

	while (wall->hit == 0)
	{
		if (wall->sideDistX < wall->sideDistY)
		{
			wall->sideDistX += wall->deltaDistX;
			wall->mapX += wall->stepX;
			if (wall->stepX == 1)
				wall->side = 0;
			else if (wall->stepX == -1)
				wall->side = 1;
		}
		else
		{
			wall->sideDistY += wall->deltaDistY;
			wall->mapY += wall->stepY;
			if (wall->stepY == 1)
				wall->side = 2;
			else if (wall->stepY == -1)
				wall->side = 3;
		}
		if (game->map[wall->mapX][wall->mapY] > 0) 
			wall->hit = 1;
	}
}
void perp_wall(t_game *game, t_wall *wall)
{
	if (wall->side == 0 || wall->side == 1)
		wall->perpWallDist = (wall->mapX - game->posX + (1 - wall->stepX) / 2) / wall->rayDirX;
	else
		wall->perpWallDist = (wall->mapY - game->posY + (1 - wall->stepY) / 2) / wall->rayDirY;
	wall->lineHeight = (int)(height / wall->perpWallDist);
	wall->drawStart = -wall->lineHeight / 2 + height / 2;
	if(wall->drawStart < 0)
		wall->drawStart = 0;
	wall->drawEnd = wall->lineHeight / 2 + height / 2;
	if(wall->drawEnd >= height)
		wall->drawEnd = height - 1;
}
