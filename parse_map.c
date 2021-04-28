#include "cub3d.h"

void parse_map(int fd, char *line)
{
    int flag;
    int x;
    t_list *elem;
    char **map;
    int i;

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
    map = (char **)malloc(sizeof(char *) * i);

    while(elem)
    {
        map[x] = ft_strdup(elem->content);
        elem = elem->next;
        x++;
    }
    x = 0;
    while(x < i)
    {
        printf("%s\n",map[x]);
        x++;
    }
}