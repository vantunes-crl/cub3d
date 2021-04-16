#include "cub3d.h"

#define numSprites 19
#define uDiv 1
#define vDiv 1
#define vMove 0.0

typedef struct s_sprite
{
	double 	y;
	double 	x;
	int 	texture;
	int		spriteOrder[numSprites];
    double	spriteDistance[numSprites];
	double spriteX;
	double spriteY;
	double invDet;
	double transformX;
	double transformY;
	int spriteScreenX;
	int vMoveScreen;
	int spriteHeight;
	int drawStartY;
	int drawEndY;
	int spriteWidth;
	int drawStartX;
	int drawEndX;
} t_sprite;

t_sprite	sprite[numSprites] =
{
	{20.5, 11.5, 10},
	{18.5,4.5, 10},
	{10.0,4.5, 10},
	{10.0,12.5,10},
	{3.5, 6.5, 10},
	{3.5, 20.5,10},
	{3.5, 14.5,10},
	{14.5,20.5,10},

	{18.5, 10.5, 9},
	{18.5, 11.5, 9},
	{18.5, 12.5, 9},

	{21.5, 1.5, 8},
	{15.5, 1.5, 8},
	{16.0, 1.8, 8},
	{16.2, 1.2, 8},
	{3.5,  2.5, 8},
	{9.5, 15.5, 8},
	{10.0, 15.1,8},
	{10.5, 15.8,8},
};

void draw_sprites(t_game *game)
{
	t_sprite sprites;

    for(int i = 0; i < numSprites; i++)
	{
		sprites.spriteOrder[i] = i;
		sprites.spriteDistance[i] = ((game->posX - sprite[i].x) * (game->posX - sprite[i].x) + (game->posY - sprite[i].y) * (game->posY - sprite[i].y));
	}
	sortSprites(sprites.spriteOrder, sprites.spriteDistance, numSprites);
	for(int i = 0; i < numSprites; i++)
	{
		sprites.spriteX = sprite[sprites.spriteOrder[i]].x - game->posX;
		sprites.spriteY = sprite[sprites.spriteOrder[i]].y - game->posY;
		sprites.invDet = 1.0 / (game->planeX * game->dirY - game->dirX * game->planeY);
		sprites.transformX = sprites.invDet * (game->dirY * sprites.spriteX - game->dirX * sprites.spriteY);
		sprites.transformY = sprites.invDet * (-game->planeY * sprites.spriteX + game->planeX * sprites.spriteY);
		sprites.spriteScreenX = (int)((width / 2) * (1 + sprites.transformX / sprites.transformY));
		sprites.vMoveScreen = (int)(vMove / sprites.transformY);
		sprites.spriteHeight = (int)fabs((height / sprites.transformY) / vDiv);
		sprites.drawStartY = -sprites.spriteHeight / 2 + height / 2 + sprites.vMoveScreen;
		if (sprites.drawStartY < 0) 
			sprites.drawStartY = 0;
		sprites.drawEndY = sprites.spriteHeight / 2 + height / 2 + sprites.vMoveScreen;
		if(sprites.drawEndY >= height) 
			sprites.drawEndY = height - 1;
		sprites.spriteWidth = (int)fabs((height / sprites.transformY) / uDiv);
		sprites.drawStartX = -sprites.spriteWidth / 2 + sprites.spriteScreenX;
		if(sprites.drawStartX < 0) 
			sprites.drawStartX = 0;
		sprites.drawEndX = sprites.spriteWidth / 2 + sprites.spriteScreenX;
		if(sprites.drawEndX >= width) 
			sprites.drawEndX = width - 1;
		for(int stripe = sprites.drawStartX; stripe < sprites.drawEndX; stripe++)
		{
			int texX = (int)((256 * (stripe - (-sprites.spriteWidth / 2 + sprites.spriteScreenX)) * texWidth / sprites.spriteWidth) / 256);
			if(sprites.transformY > 0 && stripe > 0 && stripe < width && sprites.transformY < game->zBuffer[stripe])
			for(int y = sprites.drawStartY; y < sprites.drawEndY; y++)
			{
				int d = (y-sprites.vMoveScreen) * 256 - height * 128 + sprites.spriteHeight * 128;
				int texY = ((d * texHeight) / sprites.spriteHeight) / 256;
				int color = game->texture[sprite[sprites.spriteOrder[i]].texture][texWidth * texY + texX];
                if((color & 0x00FFFFFF) != 0) game->buf[y][stripe] = color;
			}
		}
	}
}

