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
		game->bmp_buf[wall->y][wall->x] = textures->color;
	}
}