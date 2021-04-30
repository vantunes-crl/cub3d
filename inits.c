#include "cub3d.h"

void	draw(t_game *game)
{
    int y;
    int x;

    y = 0;
	while (y < game->height_screen)
	{
        x = 0;
		while (x < game->width_screen)
		{
			game->img.data[y * game->width_screen + x] = game->buf[y][x];
            x++;
		}
        y++;
	}
}

void	load_image(t_game *game, int *texture, char *path, t_img *img)
{
    int y;

    y = 0;
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
}

void	load_texture(t_game *game)
{
	t_img	img;

	load_image(game, game->texture[0], game->tex_south, &img);
	load_image(game, game->texture[1], game->tex_north, &img);
	load_image(game, game->texture[2], game->tex_east, &img);
	load_image(game, game->texture[3], game->tex_west, &img);
	load_image(game, game->texture[4], "textures/lava.xpm", &img);
	load_image(game, game->texture[5], "textures/mossy.xpm", &img);
	load_image(game, game->texture[6], "textures/galaxy.xpm", &img);
	load_image(game, game->texture[7], "textures/purplestone.xpm", &img);
    load_image(game, game->texture[8], "textures/barrel.xpm", &img);
	load_image(game, game->texture[9], "textures/golddoor.xpm", &img);
	load_image(game, game->texture[10], game->tex_sprite, &img);
}