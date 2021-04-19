#include "cub3d.h"

void	calc(t_game *game , t_flor flor)
{
	t_cell cell;
	t_wall wall;
	t_textures textures;

	init_map(game);

	flor.y = 0;
	while(flor.y < game->height)
	{
		flor = put_flor(flor,game);
		cell.x = 0;
		while (++cell.x < game->width)
			cell = put_cell(game,&flor, cell);
		flor.y++;
	}
	wall.x = 0;
	if (game->map[(int)(game->posX + game->dirX * game->moveSpeed)][(int)(game->posY)] == 10)
		game->map[(int)(game->posX + game->dirX * game->moveSpeed )][(int)(game->posY)] = 0;
	else if (game->map[(int)(game->posX)][(int)(game->posY + game->dirY * game->moveSpeed )] == 10)
		game->map[(int)(game->posX)][(int)(game->posY + (game->dirY) * game->moveSpeed)] = 0;
	while (++wall.x < game->width)
	{
		init_wall(&wall,game);
		steps(&wall, game);
		perp_wall(game, &wall);
		textures_wall(&wall,&textures,game);
		draw_wall(game,&textures, &wall);
		game->zBuffer[wall.x] = wall.perpWallDist;
	}
	draw_sprite(game,11, 5, 10);
	draw_sprite(game,5,5,10);
}

int	main_loop(t_game *game)
{
	t_flor flor;

	calc(game, flor);
	draw(game);
	draw_rectangles(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	mlx_string_put(game->mlx, game->win ,50, 350, 0xFFFFFF, ft_itoa((int)game->posX));
	mlx_string_put(game->mlx, game->win ,20, 350, 0xFFFFFF, ft_itoa((int)game->posY));
	return (0);
}

int init_buff(t_game *game)
{
	int i;
	int j;
	
	i = 0;
	game->zBuffer = (double *)malloc(sizeof(double *) * game->width);
	game->buf = (int **)malloc(sizeof(int *) * game->height);
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
	game.width = 1920;
	game.height = 1024;
	init_buff(&game);
	init_map(&game);
	load_texture(&game);
	game.posX = 5.0;
	game.posY = 10.0;
	game.dirX = -1.0;
	game.dirY = 0.0;
	game.planeX = 0.0;
	game.planeY = 0.90;
	game.moveSpeed = 0.11;
	game.rotSpeed = 0.11;
	game.win = mlx_new_window(game.mlx, game.width, game.height, "mlx");
	game.img.img = mlx_new_image(game.mlx, game.width, game.height);
	game.img.data = (int *)mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.size_l, &game.img.endian);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS,0, &key_press, &game);
	mlx_loop(game.mlx);
}
