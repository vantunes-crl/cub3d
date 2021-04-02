#include "cub3d.h"

int		main_loop(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	draw_rectangles(game); // map squares
	draw_lines(game); // lines for divide the squares
	draw_player(game); // player 
	draw_line(game,game->pdx + game->px, game->pdy + game->py, game->px , game->py); // line between the player and angol
	return (0);
}

int main()
{
	t_game	game;

	game.px = 4; //player incial position
	game.py = 3; //player incial position
	game.pdx = cos(game.pa) * 5; //inicial player view
	game.pdy = sin(game.pa) * 5; 

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3d"); //funcao que inicia a janela
	map_init(&game); // funcao que inicia o mapa
	img_init(&game); //inicia a imagem
	mlx_hook(game.win, EVENT_KEY_PRESS, 1<<0L, &key_press, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);

	mlx_loop(game.mlx);
}