#include "cub3d.h"

void parse_floor(t_game *game, char *line, int i)
{
    char buff[4];
    char buff2[4];
    char buff3[4];
    int j;

    j = 0;
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
    game->floorcolor = create_trgb(ft_atoi(buff),ft_atoi(buff2),ft_atoi(buff3));

}

void parse_screen(t_game *game ,char *line, int i)
{
    char width[5];
    char height[5];
    int j;

    j = 0;
    while(line[i] != '\0')
    {
        if (line[i] >= '0' && line[i] <= '9')
        {
            while(line[i] >= '0' && line[i] <= '9')
                width[j++] = line[i++];
            width[j] = '\0';
            j = 0;
            i++;
            while(line[i] >= '0' && line[i] <= '9')
                height[j++] = line[i++];
            height[j] = '\0';
            break;
        }
        i++;
    }
    game->width = ft_atoi(width);
    game->height = ft_atoi(height);
}

void parse_cell(t_game *game, char *line, int i)
{
    char buff[4];
    char buff2[4];
    char buff3[4];
    int j;

    j = 0;
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
    game->cellcolor = create_trgb(ft_atoi(buff),ft_atoi(buff2),ft_atoi(buff3));
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
        while(line[i] != '\0') // primeira linha
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
                parse_sprite(game, line, i + 1);
            if (line[i] == 'F')
                parse_floor(game, line, i);
            if (line[i] == 'C')
                parse_cell(game, line, i);
            i++;
        }
    }
    close(fd);
}