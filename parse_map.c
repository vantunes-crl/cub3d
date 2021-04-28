#include "cub3d.h"

void parse_map(t_game *game)
{
    int flag;
    int x;
    char *line;
    t_list *elem;
    int i;
    int fd;

    fd = open("inits.cub",O_RDONLY);
    flag = 0;
    x = 0;
    elem = NULL;
    while (get_next_line(fd, &line))
    {   
        if (line[0] == '1')
            flag = 1;
        if (flag == 1)
            ft_lstadd_back(&elem,ft_lstnew((void *)line));
    }

    i = ft_lstsize(elem);
    game->map = (char **)malloc(sizeof(char *) * i);

    while(elem)
    {
        game->map[x] = ft_strdup(elem->content);
        elem = elem->next;
        x++;
    }
    close(fd);
}