#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "cub3d.h"
#define BUFFER_SIZE 0

int				get_next_line(const int fd, char **line);
int				check_line(char *str);
int				ft_len(const char *str);
void			*ft_memmove(void *dst, const void *src, size_t len);
char			*str_join(char const *s1, char const *s2);

#endif