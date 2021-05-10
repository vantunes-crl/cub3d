#include "cub3d.h"

int	main_loop(t_game *game)
{
	calc(game);
	draw(game);
	draw_rectangles(game);
	key_move(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

void	init_game(t_game *game)
{
	game->screenshot = 0;
	game->moveSpeed = 0.08;
	game->rotSpeed = 0.08;
	game->key_w = 0;
	game->key_s = 0;
	game->key_a = 0;
	game->key_d = 0;
	game->key_esc = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;
	
	init_game(&game);
	if (argc == 3)
	{	
		if (ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) == 0)
			game.screenshot = 1;
	}
	game.mlx = mlx_init();
	parse(&game, argv[1]);
	player_init(&game);
	init_buff1(&game);
	load_texture(&game);
	game.win = mlx_new_window(game.mlx,
			game.width_screen, game.height_screen, "mlx");
	game.img.img = mlx_new_image(game.mlx,
			game.width_screen, game.height_screen);
	game.img.data = (int *)mlx_get_data_addr(game.img.img,
			&game.img.bpp, &game.img.size_l, &game.img.endian);
	if (game.screenshot == 1)
		creat_bmp(&game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_hook(game.win, 2, 1L << 0, &key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, &key_release, &game);
	mlx_loop(game.mlx);
}
