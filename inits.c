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
	int x;

    y = 0;
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			x++;
		}
		y++;
	}
}

void	load_texture(t_game *game)
{
	t_img	img;

	load_image(game, game->texture[0], game->tex_south, &img);
	load_image(game, game->texture[1], game->tex_north, &img);
	load_image(game, game->texture[2], game->tex_east, &img);
	load_image(game, game->texture[3], game->tex_west, &img);
	load_image(game, game->texture[4], game->tex_sprite, &img);
}

void	draw_all(t_game *game)
{
    int y;
    int x;

    y = 0;
	while (y < game->height_screen)
	{
        x = 0;
		while (x < game->width_screen)
		{
			game->bmp_buf[y][x] = game->img.data[y * game->width_screen + x];
            x++;
		}
        y++;
	}
}

int init_buff1(t_game *game)
{
	int i;

	game->texture = calloc(5, sizeof(int *));
	i = -1;
	while (++i < 5)
		game->texture[i] = calloc(texHeight * texWidth, sizeof(int));
	game->zBuffer = calloc(game->width_screen, sizeof(double *));
	game->buf = calloc(game->height_screen, sizeof(int *));
	i = -1;
	while(++i < game->height_screen)
		game->buf[i] = calloc(game->width_screen, sizeof(int *));
	return (0);
}