#include "cub3d.h"

void	textures_wall(t_wall *wall, t_textures *textures, t_game *game)
{
	double	norm;

	if (wall->side == 0 || wall->side == 1)
		textures->wallX = game->posY + wall->perpWallDist * wall->rayDirY;
	else
		textures->wallX = game->posX + wall->perpWallDist * wall->rayDirX;
	textures->wallX -= floor(textures->wallX);
	textures->texX = (int)(textures->wallX * (double)TEXWIDTH);
	if (wall->side == 0 && wall->rayDirX > 0)
		textures->texX = TEXWIDTH - textures->texX - 1;
	if (wall->side == 1 && wall->rayDirY < 0)
		textures->texX = TEXWIDTH - textures->texX - 1;
	textures->step = 1.0 * TEXHEIGHT / wall->lineHeight;
	norm = (wall->drawStart - game->height_screen / 2 + wall->lineHeight / 2);
	textures->texPos = norm * textures->step;
}

void	draw_wall(t_game *game, t_textures *textures, t_wall *wall)
{
	int	norm;

	wall->y = wall->drawStart;
	while (wall->y++ < wall->drawEnd)
	{
		textures->texY = (int)textures->texPos & (TEXHEIGHT - 1);
		textures->texPos += textures->step;
		norm = TEXHEIGHT * textures->texY + textures->texX;
		if (wall->side == 0)
			textures->color = game->texture[0][norm];
		else if (wall->side == 1)
			textures->color = game->texture[1][norm];
		else if (wall->side == 2)
			textures->color = game->texture[2][norm];
		else if (wall->side == 3)
			textures->color = game->texture[3][norm];
		game->buf[wall->y][wall->x] = textures->color;
	}
}

void	hit_wall(t_game *game, t_wall *wall)
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

void	wall_calc(t_wall *wall, t_game *game, t_textures *textures)
{
	t_flor	flor;
	t_cell	cell;

	flor.y = 0;
	while (flor.y < game->height_screen)
	{
		flor = put_flor(flor, game);
		cell.x = 0;
		while (++cell.x < game->width_screen)
			cell = put_cell(game, &flor, cell);
		flor.y++;
	}
	wall->x = 0;
	while (++wall->x < game->width_screen)
	{
		init_wall(wall, game);
		steps(wall, game);
		perp_wall(game, wall);
		textures_wall(wall, textures, game);
		draw_wall(game, textures, wall);
		game->zBuffer[wall->x] = wall->perpWallDist;
	}
}

void	calc(t_game *game)
{
	t_wall		wall;
	t_textures	textures;
	int			i;
	int			j;

	wall_calc(&wall, game, &textures);
	i = 0;
	while (i < game->map_size)
	{
		j = 0;
		while (j < ft_strlen(game->map[i]))
		{
			if (game->map[i][j] == '2')
				draw_sprite(game, i, j);
			j++;
		}
		i++;
	}
}
