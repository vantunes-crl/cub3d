#include "cub3d.h"

int main()
{
    t_game game;

    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3d");
    game.img.img = mlx_new_image(game.mlx , WIDTH, HEIGHT);
    game.img.data = mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.sizel, &game.img.endian);
    map_init(&game);
    vertical_line(&game , 10,5,500,0xFFFFFF); 
    mlx_put_image_to_window(game.mlx,game.win,game.img.img, 0, 0);

    mlx_loop(game.mlx);
}