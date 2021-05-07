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

void parse(t_game *game , char *argv)
{
    int fd;
    int i;
    char *line;
    t_list *elem;
    int x;

    elem = NULL;
    x = 0;
    
    if (game->screenshot)
        fd = open("inits.cub", O_RDONLY);
    else
        fd = open(argv, O_RDONLY);
    while (get_next_line(fd,&line))
    {
        if (line[0] == 'R')
            parse_screen(game,line,i);
        else if (line[0] == 'N' && line[1] == 'O')
            parse_side(game, line, 2, 0);
        else if (line[0] == 'S' && line[1] == 'O')
            parse_side(game, line, 2, 1);
        else if (line[0] == 'W' && line[1] == 'E')
            parse_side(game, line, 2, 2);
        else if (line[0] == 'E' && line[1] == 'A')
            parse_side(game, line, 2, 3);
        else if (line[0] == 'S' && line[1] == ' ')
            parse_side(game, line, 2, 4);
        else if (line[0] == 'F' && line[1] == ' ')
            parse_floor(game, line);
        else if (line[0] == 'C' && line[1] == ' ')
            parse_cell(game, line);
        else
        {
            i = 0;
            while(line[i])
            {
                if (line[i] == '1')
                {
                    ft_lstadd_back(&elem,ft_lstnew((void *)line));
                    break;
                }
                i++;
            }
        }
    }
    i = ft_lstsize(elem);
    game->map_size = i;
    game->map = (char **)malloc(sizeof(char *) * i);
    while(elem)
    {
        game->map[x] = ft_strdup(elem->content);
        elem = elem->next;
        x++;
    }
    check_map(game,i);
    close(fd);
}

void check_map(t_game *game, int size_map)
{
    int x;
    int j;

    x = 0;
    j = 0;
    while(x < size_map)
    {
        j = 0;
        while(j < ft_strlen(game->map[x]))
        {
            if (x == 0 || j == 0)
            {
               if (!(ismap(game->map[x][j])))
               {
                   printf("Map Error");
                   exit(0);
               }
            }
            else if ((x == size_map - 1) || (j + 1 == ft_strlen(game->map[x])))
            {
                if (!(ismap(game->map[x][j])))
                {
                    printf("Map Error");
                    exit(0);
                }
            }
            if (!((x == size_map - 1 || j + 1 == ft_strlen(game->map[x])) || (x == 0 || j == 0)))
            {
                if ((game->map[x][j] == '0' && !game->map[x - 1][j]) || (game->map[x][j] == '0' && game->map[x - 1][j] == ' '))
                {
                    printf("Map Error");
                    exit(0);
                }
                else if ((game->map[x][j] == '0' && !game->map[x + 1][j]) || (game->map[x][j] == '0' && game->map[x + 1][j] == ' '))
                {
                    printf("Map Error");
                    exit(0);
                }
            }
            j++;
        }
        x++;
    }
}