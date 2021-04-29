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
                game->posY = i;
                game->posX = j;
                game->map[i][j] = '0';
                break;
            }
            j++;
        }
        i++;
    }
}