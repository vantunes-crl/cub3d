#include "cub3d.h"

void	calc(t_game *game , t_flor flor)
{
	t_cell cell;
	t_wall wall;
	t_textures textures;

	flor.y = 0;
	while(flor.y < game->height_screen)
	{
		flor = put_flor(flor,game);
		cell.x = 0;
		while (++cell.x < game->width_screen)
			cell = put_cell(game,&flor, cell);
		flor.y++;
	}
	wall.x = 0;
	while (++wall.x < game->width_screen)
	{
		init_wall(&wall,game);
		steps(&wall, game);
		perp_wall(game, &wall);
		textures_wall(&wall,&textures,game);
		draw_wall(game,&textures, &wall);
		game->zBuffer[wall.x] = wall.perpWallDist;
	}
	draw_sprites(game);
}

int	main_loop(t_game *game)
{
	t_flor flor;

	calc(game, flor);
	draw(game);
	draw_rectangles(game);
	key_move(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

int init_buff(t_game *game)
{
	int i;
	int j;

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
	game->texture = (int **)malloc(sizeof(int *) * 11);
	if (!game->texture)
		return (-1);
	i = 0;
	while (i < 11)
	{
		game->texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth));
		if (!game->texture)
			return (-1);
		i++;
	}
	i = 0;
	while(i < 11)
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
	init_map(&game);
	parse(&game);
	init_buff(&game);
	load_texture(&game);
	game.posX = 5.0;
	game.posY = 10.0;
	game.dirX = -1.0;
	game.dirY = 0.0;
	game.planeX = 0.0;
	game.planeY = 0.90;
	game.moveSpeed = 0.08;
	game.rotSpeed = 0.08;
	game.key_w = 0;
	game.key_s = 0;
	game.key_a = 0;
	game.key_d = 0;
	game.key_esc = 0;
	game.win = mlx_new_window(game.mlx, game.width_screen, game.height_screen, "mlx");
	game.img.img = mlx_new_image(game.mlx, game.width_screen, game.height_screen);
	game.img.data = (int *)mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.size_l, &game.img.endian);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_hook(game.win, 2, 0, &key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, &key_release, &game);
	mlx_loop(game.mlx);
}
