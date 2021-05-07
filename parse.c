#include "cub3d.h"

void chose_side(t_game *game , int side, char *texture)
{
     if (side == 0)
        game->tex_north = ft_strdup(texture);
    if (side == 1)
        game->tex_south = ft_strdup(texture);
    if (side == 2)
        game->tex_east = ft_strdup(texture);
    if (side == 3)
        game->tex_west = ft_strdup(texture);
    if (side == 4)
        game->tex_sprite = ft_strdup(texture);
}

void parse_side(t_game *game, char *line, int i, int side)
{
    int count;
    int j;
    char *texture;

    count = 0;
    j = 0;
    while (ft_isalpha(line[i]) == 0)
        i++;
    while(ft_isalpha(line[i++]) || line[i++] == '.' || line[i++] == '/')
        count++;
    i = 2;
    texture = (char *)malloc(sizeof(char *) * count + 1);
    while(ft_isalpha(line[i]) == 0)
        i++;
    while(ft_isalpha(line[i]) || line[i] == '.' || line[i] == '/')
        texture[j++] = line[i++];
    texture[j] = '\0';
    chose_side(game,side,texture);
    free(texture);
}