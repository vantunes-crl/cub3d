#include "cub3d.h"

void textures_wall(t_wall *wall, t_textures *textures, t_game *game)
{
	if (wall->side == 0 || wall->side == 1)
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
	textures->texPos = (wall->drawStart - game->height_screen / 2 + wall->lineHeight / 2) * textures->step;
}

void draw_wall(t_game *game, t_textures *textures, t_wall *wall)
{
	wall->y = wall->drawStart;
	while (wall->y++ < wall->drawEnd)
	{
		textures->texY = (int)textures->texPos & (texHeight - 1);
		textures->texPos += textures->step;
		if (wall->side == 0)
			textures->color = game->texture[0][texHeight * textures->texY + textures->texX];
		else if (wall->side == 1)
			textures->color = game->texture[1][texHeight * textures->texY + textures->texX];
		else if (wall->side == 2)
			textures->color = game->texture[2][texHeight * textures->texY + textures->texX];
		else if (wall->side == 3)
			textures->color = game->texture[3][texHeight * textures->texY + textures->texX];
		game->buf[wall->y][wall->x] = textures->color;
	}
}

void hit_wall(t_game *game, t_wall *wall)
{
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
		if (game->map[wall->mapX][wall->mapY] == '1')
			wall->hit = 1;
	}
}