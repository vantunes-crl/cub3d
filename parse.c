#include "cub3d.h"

void parse_screen(char *line, int i)
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
}

void parse()
{
    int fd;
    int i;
    char *line;
    int j;

    i = 0;
    fd = open("inits.cub", O_RDONLY);
    get_next_line(fd,&line);
    while(line[i] != '\0') // primeira linha
    {
        if (line[i] == 'R')
            parse_screen(line,i);
        i++;
    }
}