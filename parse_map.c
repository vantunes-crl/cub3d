#include "cub3d.h"

void map_check(t_game *game)
{
    int i;
    int j;

    i = 0;

    while (i < game->map_size)
    {
        j = 0;
        while (j < ft_strlen(game->map[i]))
        {
            if (game->map[i][j] == 'N')
            {
                game->posY = j + 0.5;
                game->posX = i + 0.5;
                game->dirX = -1.0;
                game->dirY = 0.0;
                game->planeX = 0.0;
		        game->planeY = 0.66;
                game->map[i][j] = '0';
                break;
            }
            if (game->map[i][j] == 'S')
            {
                game->posY = j + 0.5;
                game->posX = i + 0.5;
                game->dirX = 0.999767;
		        game->dirY = -0.021591;
		        game->planeX = -0.014250;
		        game->planeY = -0.659846;
                game->map[i][j] = '0';
                break;
            }
            if (game->map[i][j] == 'W')
            {
                game->posY = j + 0.5;
                game->posX = i + 0.5;
                game->dirX = 0.029200;
		        game->dirY = -0.999574;
		        game->planeX = -0.659719;
		        game->planeY = -0.019272;
                game->map[i][j] = '0';
                break;
            }
            if (game->map[i][j] == 'E')
            {
                game->posY = j + 0.5;
                game->posX = i + 0.5;
                game->dirX = 0.029200;
		        game->dirY = 0.999573;
		        game->planeX = 0.659718;
		        game->planeY = -0.019272;
                game->map[i][j] = '0';
                break;
            }
            j++;
        }
        i++;
    }
}

int ismap(char c)
{
    if (c == ' ' || c == '1')
        return (1);
    return (0);
}