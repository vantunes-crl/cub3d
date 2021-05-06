#include "cub3d.h"


void	calc(t_game *game)
{
	t_cell cell;
	t_wall wall;
	t_flor flor;
	t_textures textures;
	int i;
	int j;

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
	i = 0;
	while (i < game->map_size)
    {
        j = 0;
        while (j < ft_strlen(game->map[i]))
        {
            if (game->map[i][j] == '2')
               draw_sprite(game,i,j);
            j++;
        }
        i++;
    }
}

int	main_loop(t_game *game)
{
	calc(game);
	draw(game);
	draw_rectangles(game);
	key_move(game);
	if (!game->screenshot)
		mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
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

int	main(int argc, char **argv)
{
	t_game game;
	
	game.screenshot = 0;
	if (argc < 2)
		exit(0);
	if (ft_strncmp("--save",argv[1],5) == 0)
		game.screenshot = 1;
	game.mlx = mlx_init();
	parse(&game,argv[1]);
	player_check(&game);
	init_buff(&game);
	init_bpm_buf(&game);
	load_texture(&game);
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
	if (game.screenshot)
	{
		int fd;
		int fz;

		fz = 54 + (3 * ((int)game.height_screen) * (int)game.width_screen);
		calc(&game);
		draw(&game);
		draw_rectangles(&game);
		fd = open("screenshot.bmp", O_WRONLY | O_CREAT, 0777 | O_TRUNC | O_APPEND);
		write_bmp_header(fd, fz, &game);
		write_bmp_data(fd,&game);
		close(0);
		exit(0);
	}
	else
		mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_hook(game.win, 2, 1L << 0, &key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, &key_release, &game);
	mlx_loop(game.mlx);
}
