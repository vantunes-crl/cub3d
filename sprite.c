#include "cub3d.h"

void draw_sprite(t_game *game , double pos_x, double pos_y)
{
	t_sprite sprites;

	sprites.spriteX = (int)pos_x - game->posX;
	sprites.spriteY = (int)pos_y - game->posY;
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
			sprites.color = game->texture[4][texWidth * sprites.texY + sprites.texX];
			if ((sprites.color & 0x00FFFFFF) != 0)
			{
				game->buf[sprites.j][sprites.stripe] = sprites.color;
				game->bmp_buf[sprites.j][sprites.stripe] = sprites.color;
			}
			sprites.j++;
		}
		sprites.stripe++;
	}
}