#include "cub3d.h"

void textures_wall(t_wall *wall, t_textures *textures, t_game *game)
{
	textures->texNum = game->map[wall->mapX][wall->mapY] - 1;
	if (wall->side == 0)
		textures->wallX = game->posY + wall->perpWallDist * wall->rayDirY;
	else
		textures->wallX = game->posX + wall->perpWallDist * wall->rayDirX;
	textures->wallX -= floor(textures->wallX);
	textures->texX = (int)(textures->wallX * (double)texWidth);
	if (wall->side == 0 && wall->rayDirX > 0)
		textures->texX = texWidth - textures->texX - 1;
	if (wall->side == 1 && wall->rayDirY < 0)
		textures->texX = texWidth - textures->texX - 1;
	textures->step = 1.0 * texHeight / wall->lineHeight;
	textures->texPos = (wall->drawStart - height / 2 + wall->lineHeight / 2) * textures->step;
}

void draw_wall(t_game *game, t_textures *textures, t_wall *wall)
{
	wall->y = wall->drawStart;
	while (wall->y++ < wall->drawEnd)
	{
		textures->texY = (int)textures->texPos & (texHeight - 1);
		textures->texPos += textures->step;
		textures->color = game->texture[textures->texNum][texHeight * textures->texY + textures->texX];
		if (wall->side == 1)
			textures->color = (textures->color >> 1) & 8355711;
		game->buf[wall->y][wall->x] = textures->color;
	}
}

void floor_wall(t_wall *wall, t_textures *textures)
{
	if(wall->side == 0 && wall->rayDirX > 0)
	{
		wall->floorXWall = wall->mapX;
		wall->floorYWall = wall->mapY + textures->wallX;
	}
	else if(wall->side == 0 && wall->rayDirX < 0)
	{
		wall->floorXWall = wall->mapX + 1.0;
		wall->floorYWall = wall->mapY + textures->wallX;
	}
	else if(wall->side == 1 && wall->rayDirY > 0)
	{
		wall->floorXWall = wall->mapX + textures->wallX;
		wall->floorYWall = wall->mapY;
	}
	else
	{
		wall->floorXWall = wall->mapX + textures->wallX;
		wall->floorYWall = wall->mapY + 1.0;
	}
}
void flor_wall2(t_game *game, t_textures *textures, t_wall *wall, t_flor *flor)
{
	textures->distWall = wall->perpWallDist;
	textures->distPlayer = 0.0;
	if (wall->drawEnd < 0) 
		wall->drawEnd = height;
	for(textures->y = wall->drawEnd + 1; textures->y < height; textures->y++)
	{
		textures->currentDist = height / (2.0 * textures->y - height);
		wall->weight = (textures->currentDist - textures->distPlayer) / (textures->distWall - textures->distPlayer);
		flor->currentFloorX = wall->weight * wall->floorXWall + (1.0 - wall->weight) * game->posX;
		flor->currentFloorY = wall->weight * wall->floorYWall + (1.0 - wall->weight) * game->posY;
		flor->floorTexX = (int)(flor->currentFloorX * texWidth) % texWidth;
		flor->floorTexY = (int)(flor->currentFloorY * texHeight) % texHeight;
		flor->checkerBoardPattern = ((int)(flor->currentFloorX) + (int)(flor->currentFloorY)) % 2;
		if(flor->checkerBoardPattern == 0)
			textures->floorTexture = 3;
		else 
			textures->floorTexture = 4;
		game->buf[textures->y][wall->x] = (game->texture[textures->floorTexture][texWidth * flor->floorTexY + flor->floorTexX] >> 1) & 8355711;
		game->buf[height - textures->y][wall->x] = game->texture[6][texWidth * flor->floorTexY + flor->floorTexX];
	}
}