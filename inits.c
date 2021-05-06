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

int init_buff(t_game *game)
{
	int i;
	int j;

	i = 0;
	game->zBuffer = (double *)malloc(sizeof(double *) * game->width_screen);
	while(i < game->width_screen)
	{
		game->zBuffer[i] = 0;
		i++;
	}
	i = 0;
	game->buf = (int **)malloc(sizeof(int *) * game->height_screen);
	while(i < game->height_screen)
	{
		game->buf[i] = (int *)malloc(sizeof(int *) * game->width_screen);
		i++;
	}
	i = 0;
	while (i < game->height_screen)
	{
		j = 0;
		while (j < game->width_screen)
		{
			game->buf[i][j] = 0;
			j++;
		}
		i++;
	}
	game->texture = (int **)malloc(sizeof(int *) * 5);
	if (!game->texture)
		return (-1);
	i = 0;
	while (i < 5)
	{
		game->texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth));
		if (!game->texture)
			return (-1);
		i++;
	}
	i = 0;
	while(i < 5)
	{
		j = 0;
		while (j < texHeight * texWidth)
		{
			game->texture[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}
