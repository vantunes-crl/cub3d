#include "cub3d.h"

void parse_sprite(t_game *game, char *line, int i)
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
    game->tex_sprite = (char *)malloc(sizeof(char *) * count + 1);
    while(ft_isalpha(line[i]) == 0)
        i++;
    while(ft_isalpha(line[i]) || line[i] == '.' || line[i] == '/')
        game->tex_sprite[j++] = line[i++];
    game->tex_sprite[j] = '\0';
}

void parse_screen(t_game *game ,char *line, int i)
{
    char width_screen[5];
    char height_screen[5];
    int j;

    j = 0;
    while(line[i] != '\0')
    {
        if (line[i] >= '0' && line[i] <= '9')
        {
            while(line[i] >= '0' && line[i] <= '9')
                width_screen[j++] = line[i++];
            width_screen[j] = '\0';
            j = 0;
            i++;
            while(line[i] >= '0' && line[i] <= '9')
                height_screen[j++] = line[i++];
            height_screen[j] = '\0';
            break;
        }
        i++;
    }
    game->width_screen = ft_atoi(width_screen);
    game->height_screen = ft_atoi(height_screen);
}

void parse(t_game *game)
{
    int fd;
    int i;
    char *line;

    i = 0;
    fd = open("inits.cub", O_RDONLY);
    while (get_next_line(fd,&line) > 0)
    {
        i = 0;
        while(line[i] != '\0')
        {
            if (line[i] == 'R')
                parse_screen(game,line,i);
            if (line[i] == 'N' && line[i + 1] == 'O')
                parse_north(game, line, i + 2);
            if (line[i] == 'S' && line[i + 1] == 'O')
                parse_south(game, line, i + 2);
            if (line[i] == 'W' && line[i + 1] == 'E')
                parse_west(game, line, i + 2);
            if (line[i] == 'E' && line[i + 1] == 'A')
                parse_east(game, line, i + 2);
            if (line[i] == 'S')
                parse_sprite(game, line, i + 2);
            i++;
        }
    }
}