#include "cub3d.h"

void	draw_sprites_half2(t_game *game, t_sprite *sp)
{
	double	n;

	n = sp->spriteHeight;
	if (sp->drawStartY < 0)
		sp->drawStartY = 0;
	sp->drawEndY = n / 2 + game->height_screen / 2 + sp->vMoveScreen;
	if (sp->drawEndY >= game->height_screen)
		sp->drawEndY = game->height_screen - 1;
	sp->spriteWidth = (int)fabs((game->height_screen / sp->transformY) / 1);
	sp->drawStartX = -sp->spriteWidth / 2 + sp->spriteScreenX;
	if (sp->drawStartX < 0)
		sp->drawStartX = 0;
	sp->drawEndX = sp->spriteWidth / 2 + sp->spriteScreenX;
	if (sp->drawEndX >= game->width_screen)
		sp->drawEndX = game->width_screen - 1;
	sp->stripe = sp->drawStartX;
}

void	draw_sprites_half(t_game *game, t_sprite *sp)
{
	int		n;
	double	spw;

	while (sp->stripe < sp->drawEndX)
	{
		spw = -sp->spriteWidth;
		n = (int)((256 * (sp->stripe - (spw / 2 + sp->spriteScreenX))));
		sp->texX = n * TEXWIDTH / sp->spriteWidth / 256;
		if (sp->transformY > 0 && sp->stripe > 0
			&& sp->stripe < game->width_screen
			&& sp->transformY < game->zBuffer[sp->stripe])
			sp->j = sp->drawStartY;
		while (sp->j < sp->drawEndY)
		{
			spw = (sp->j - sp->vMoveScreen);
			n = sp->spriteHeight;
			sp->d = spw * 256 - game->height_screen * 128 + n * 128;
			sp->texY = ((sp->d * TEXHEIGHT) / sp->spriteHeight) / 256;
			sp->color = game->texture[4][TEXWIDTH * sp->texY + sp->texX];
			if ((sp->color & 0x00FFFFFF) != 0)
				game->buf[sp->j][sp->stripe] = sp->color;
			sp->j++;
		}
		sp->stripe++;
	}
}

void	draw_sprite(t_game *game, double pos_x, double pos_y)
{
	t_sprite	sp;
	double		norm;

	sp.spriteX = (int)pos_x + 0.5 - game->posX;
	sp.spriteY = (int)pos_y + 0.5 - game->posY;
	norm = (game->planeX * game->dirY - game->dirX * game->planeY);
	sp.invDet = 1.0 / norm;
	norm = (game->dirY * sp.spriteX - game->dirX * sp.spriteY);
	sp.transformX = sp.invDet * norm;
	norm = (-game->planeY * sp.spriteX + game->planeX * sp.spriteY);
	sp.transformY = sp.invDet * norm;
	norm = (1 + sp.transformX / sp.transformY);
	sp.spriteScreenX = (int)((game->width_screen / 2) * norm);
	sp.vMoveScreen = (int)(0.0 / sp.transformY);
	sp.spriteHeight = (int)fabs((game->height_screen / sp.transformY) / 1);
	norm = 2 + sp.vMoveScreen;
	sp.drawStartY = -sp.spriteHeight / 2 + game->height_screen / norm;
	draw_sprites_half2(game, &sp);
	draw_sprites_half(game, &sp);
}
