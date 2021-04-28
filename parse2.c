#include "cub3d.h"

void parse_floor(t_game *game, char *line)
{
    char buff[4];
    char buff2[4];
    char buff3[4];
    int j;
    int i;

    j = 0;
    i = 0;
    while(ft_isdigit(line[i]) == 0)
        i++;
    while(ft_isdigit(line[i]) == 1)
        buff[j++] = (line[i++]);
    buff[j] = '\0';
    j = 0;
    i++;
    while(ft_isdigit(line[i]) == 1)
        buff2[j++] = (line[i++]);
    buff2[j] = '\0';
    j = 0;
    i++;
    while(ft_isdigit(line[i]) == 1)
        buff3[j++] = (line[i++]);
    buff3[j] = '\0';
    game->floor_color = create_trgb(ft_atoi(buff),ft_atoi(buff2),ft_atoi(buff3));

}
void parse_cell(t_game *game, char *line)
{
    char buff[4];
    char buff2[4];
    char buff3[4];
    int j;
    int i;

    j = 0;
    i = 0;
    while(ft_isdigit(line[i]) == 0)
        i++;
    while(ft_isdigit(line[i]) == 1)
        buff[j++] = (line[i++]);
    buff[j] = '\0';
    j = 0;
    i++;
    while(ft_isdigit(line[i]) == 1)
        buff2[j++] = (line[i++]);
    buff2[j] = '\0';
    j = 0;
    i++;
    while(ft_isdigit(line[i]) == 1)
        buff3[j++] = (line[i++]);
    buff3[j] = '\0';
    game->cell_color = create_trgb(ft_atoi(buff),ft_atoi(buff2),ft_atoi(buff3));
}

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
    while (get_next_line(fd,&line))
    {
        if (line[0] == 'R')
            parse_screen(game,line,i);
        if (line[0] == 'N' && line[1] == 'O')
            parse_north(game, line, i + 2);
        if (line[0] == 'S' && line[1] == 'O')
            parse_south(game, line, i + 2);
        if (line[0] == 'W' && line[1] == 'E')
            parse_west(game, line, i + 2);
        if (line[0] == 'E' && line[1] == 'A')
            parse_east(game, line, i + 2);
        if (line[0] == 'S' && line[1] == ' ')
            parse_sprite(game, line, i + 2);
        if (line[0] == 'F' && line[1] == ' ')
            parse_floor(game, line);
        if (line[0] == 'C' && line[1] == ' ')
            parse_cell(game, line);
        i++;
    }
    close(fd);
}