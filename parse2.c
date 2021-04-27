#include "cub3d.h"

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
            i++;
        }
    }
}