#include "cub3d.h"

#include "cub3d.h"

t_sprite	sprite[numSprites] =
{
	{20.5, 11.5, 10},
	{18.5,4.5, 10},
	{18.5, 10.5, 10},
	{21.5, 1.5, 10},
	{15.5, 1.5, 10},

};

void draw_sprites(t_game *game)
{
	t_sprite sprites;
	int i;

	i = 0;
    while (i < numSprites)
	{
		sprites.spriteOrder[i] = i;
		sprites.spriteDistance[i] = ((game->posX - sprite[i].x) * (game->posX - sprite[i].x) + (game->posY - sprite[i].y) * (game->posY - sprite[i].y));
		i++;
	}
	i = 0;
	while (i < numSprites)
	{
		sprites.spriteX = sprite[sprites.spriteOrder[i]].x - game->posX;
		sprites.spriteY = sprite[sprites.spriteOrder[i]].y - game->posY;
		sprites.invDet = 1.0 / (game->planeX * game->dirY - game->dirX * game->planeY);
		sprites.transformX = sprites.invDet * (game->dirY * sprites.spriteX - game->dirX * sprites.spriteY);
		sprites.transformY = sprites.invDet * (-game->planeY * sprites.spriteX + game->planeX * sprites.spriteY);
		sprites.spriteScreenX = (int)((game->width_screen / 2) * (1 + sprites.transformX / sprites.transformY));
		sprites.vMoveScreen = (int)(vMove / sprites.transformY);
		sprites.spriteHeight = (int)fabs((game->height_screen / sprites.transformY) / vDiv);
		sprites.drawStartY = -sprites.spriteHeight / 2 + game->height_screen / 2 + sprites.vMoveScreen;
		if (sprites.drawStartY < 0) 
			sprites.drawStartY = 0;
		sprites.drawEndY = sprites.spriteHeight / 2 + game->height_screen / 2 + sprites.vMoveScreen;
		if(sprites.drawEndY >= game->height_screen) 
			sprites.drawEndY = game->height_screen - 1;
		sprites.spriteWidth = (int)fabs((game->height_screen / sprites.transformY) / uDiv);
		sprites.drawStartX = -sprites.spriteWidth / 2 + sprites.spriteScreenX;
		if(sprites.drawStartX < 0) 
			sprites.drawStartX = 0;
		sprites.drawEndX = sprites.spriteWidth / 2 + sprites.spriteScreenX;
		if(sprites.drawEndX >= game->width_screen) 
			sprites.drawEndX = game->width_screen - 1;
		sprites.stripe = sprites.drawStartX;
		while (sprites.stripe < sprites.drawEndX)
		{
			sprites.texX = (int)((256 * (sprites.stripe - (-sprites.spriteWidth / 2 + sprites.spriteScreenX)) * texWidth / sprites.spriteWidth) / 256);
			if (sprites.transformY > 0 && sprites.stripe > 0 && sprites.stripe < game->width_screen && sprites.transformY < game->zBuffer[sprites.stripe])
				sprites.j = sprites.drawStartY;
			while (sprites.j < sprites.drawEndY)
			{
				sprites.d = (sprites.j-sprites.vMoveScreen) * 256 - game->height_screen * 128 + sprites.spriteHeight * 128;
				sprites.texY = ((sprites.d * texHeight) / sprites.spriteHeight) / 256;
				sprites.color = game->texture[sprite[sprites.spriteOrder[i]].texture][texWidth * sprites.texY + sprites.texX];
                if ((sprites.color & 0x00FFFFFF) != 0) 
					game->buf[sprites.j][sprites.stripe] = sprites.color;
				sprites.j++;
			}
			sprites.stripe++;
		}
		i++;
	}
}