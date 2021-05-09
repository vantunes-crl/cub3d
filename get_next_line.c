#include "get_next_line.h"

static	char	*rest_lane(char *save)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (!save)
		return (0);
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (0);
	}
	ret = (char *)malloc(sizeof(char) * (ft_len(save) - i) + 1);
	if (!ret)
		return (0);
	i++;
	while (save[i])
		ret[j++] = save[i++];
	ret[j] = '\0';
	free(save);
	return (ret);
}

static	char	*take_line(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	new_str = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static int	read_error(char *save)
{
	free(save);
	return (-1);
}

int	get_next_line(const int fd, char **line)
{
	static char	*save;
	char		*buff;
	int			lst_p;

	lst_p = 1;
	if (read(fd, 0, 0) || !line || BUFFER_SIZE <= 0)
		return (-1);
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (-1);
	while (!check_line(save) && lst_p != 0)
	{
		lst_p = read(fd, buff, BUFFER_SIZE);
		if (lst_p == -1)
			read_error(save);
		buff[lst_p] = '\0';
		save = str_join(save, buff);
	}
	free(buff);
	*line = take_line(save);
	save = rest_lane(save);
	if (lst_p == 0)
		return (0);
	return (1);
}
