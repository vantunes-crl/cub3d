#include "cub3d.h"

int	main_loop(t_game *game)
{
	calc(game);
	draw(game);
	draw_rectangles(game);
	key_move(game);
	return (0);
}

int init_buff(t_game *game)
{
	int i;
	int j;
	
	i = 0;
	game->zBuffer = (double *)malloc(sizeof(double *) * game->width);
	if (!game->zBuffer)
		return (0);
	game->buf = (int **)malloc(sizeof(int *) * game->height);
	if (!game->buf)
		return (0);
	while (i < game->height)
	{
		game->buf[i] = (int *)malloc(sizeof(int *) * game->width);
		i++;
	}
	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			game->buf[i][j] = 0;
			j++;
		}
		i++;
	}
	game->texture = (int **)malloc(sizeof(int *) * 5);
	if (!game->texture)
		return (0);
	i = 0;
	while (i < 5)
	{
		game->texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth));
		if (!game->texture)
			return (0);
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

int	main(void)
{
	t_game game;
	
	game.mlx = mlx_init();
	parse(&game);
	init_buff(&game);
	load_texture(&game);
	game.posX = 5.0;
	game.posY = 10.0;
	game.dirX = -1.0;
	game.dirY = 0.0;
	game.planeX = 0.0;
	game.planeY = 0.90;
	game.moveSpeed = 0.11;
	game.rotSpeed = 0.11;
	game.key_a = 0;
	game.key_w = 0;
	game.key_s = 0;
	game.key_d = 0;
	game.key_esc = 0;
	game.win = mlx_new_window(game.mlx, game.width, game.height, "mlx");
	game.img.img = mlx_new_image(game.mlx, game.width, game.height);
	game.img.data = (int *)mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.size_l, &game.img.endian);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 1L << 0, &key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, &key_release, &game);
	mlx_loop(game.mlx);
}
