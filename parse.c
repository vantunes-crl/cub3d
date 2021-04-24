#include "cub3d.h"

void parse_north(t_game *game, char *line, int i)
{
    int count;
    int j;

    count = 0;
    j = 0;
    while (ft_isalpha(line[i]) == 0)
        i++;
    while(ft_isalpha(line[i]) || line[i] == '.' || line[i] == '/')
    {
        count++;
        i++;
    }
    i = 2;
    game->tex_north = (char *)malloc(sizeof(char *) * count + 1);
    while(ft_isalpha(line[i]) == 0)
        i++;
    while(ft_isalpha(line[i]) || line[i] == '.' || line[i] == '/')
        game->tex_north[j++] = line[i++];
    game->tex_north[j] = '\0';
}

void parse_south(t_game *game, char *line, int i)
{
    int count;
    int j;

    count = 0;
    j = 0;
    while (ft_isalpha(line[i]) == 0)
        i++;
    while(ft_isalpha(line[i]) || line[i] == '.' || line[i] == '/')
    {
        count++;
        i++;
    }
    i = 2;
    game->tex_south = (char *)malloc(sizeof(char *) * count + 1);
    while(ft_isalpha(line[i]) == 0)
        i++;
    while(ft_isalpha(line[i]) || line[i] == '.' || line[i] == '/')
        game->tex_south[j++] = line[i++];
    game->tex_south[j] = '\0';
}

void parse_west(t_game *game, char *line, int i)
{
    int count;
    int j;

    count = 0;
    j = 0;
    while (ft_isalpha(line[i]) == 0)
        i++;
    while(ft_isalpha(line[i]) || line[i] == '.' || line[i] == '/')
    {
        count++;
        i++;
    }
    i = 2;
    game->tex_west = (char *)malloc(sizeof(char *) * count + 1);
    while(ft_isalpha(line[i]) == 0)
        i++;
    while(ft_isalpha(line[i]) || line[i] == '.' || line[i] == '/')
        game->tex_west[j++] = line[i++];
    game->tex_west[j] = '\0';
}

void parse_east(t_game *game, char *line , int i)
{
    int count;
    int j;

    count = 0;
    j = 0;
    while (ft_isalpha(line[i]) == 0)
        i++;
    while(ft_isalpha(line[i]) || line[i] == '.' || line[i] == '/')
    {
        count++;
        i++;
    }
    i = 2;
    game->tex_east = (char *)malloc(sizeof(char *) * count + 1);
    while(ft_isalpha(line[i]) == 0)
        i++;
    while(ft_isalpha(line[i]) || line[i] == '.' || line[i] == '/')
        game->tex_east[j++] = line[i++];
    game->tex_east[j] = '\0';
}

int		create_trgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}