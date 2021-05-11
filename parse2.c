#include "cub3d.h"

void	parse_side(t_game *game, char *line, int i, int side)
{
	int		count;
	int		j;
	char	*texture;

	count = 0;
	j = 0;
	while (ft_isalpha(line[i]) == 0)
		i++;
	while (ft_isalpha(line[i++]) || line[i++] == '.' || line[i++] == '/')
		count++;
	i = 2;
	texture = ft_calloc(count + 1, sizeof(char *));
	while (ft_isalpha(line[i]) == 0)
		i++;
	while (ft_isalpha(line[i]) || line[i] == '.' || line[i] == '/')
		texture[j++] = line[i++];
	texture[j] = '\0';
	if (!texture)
		error(game, "texture name", 0);
	chose_side(game, side, texture);
	free(texture);
}

void	parse_cell_floor_half(t_game *game, char *line, int i)
{
	int	j;

	j = 0;
	if (!ft_isdigit(line[i]))
		error(game, "caracter in color", 0);
	while (ft_isdigit(line[i]) == 1)
		game->buff2[j++] = (line[i++]);
	game->buff2[j] = '\0';
	j = 0;
	i++;
	if (!ft_isdigit(line[i]))
		error(game, "caracter in color", 0);
	while (ft_isdigit(line[i]) == 1)
		game->buff3[j++] = (line[i++]);
	game->buff3[j] = '\0';
}

void	parse_floor_cell(t_game *game, char *line, int type)
{
	int	j;
	int	i;

	j = 0;
	i = 1;
	while (!ft_isdigit(line[i]))
	{
		if ((line[i] >= 'a' && line[i] <= 'z')
			|| (line[i] >= 'A' && line[i] <= 'Z'))
			error(game, "caracter in color", 0);
		i++;
	}
	while (ft_isdigit(line[i]) == 1)
		game->buff[j++] = (line[i++]);
	game->buff[j] = '\0';
	j = 0;
	i++;
	parse_cell_floor_half(game, line, i);
	cell_or_floor(game, type);
}

t_list	*parse_infos(t_game *game, int fd, t_list *elem)
{
	char	*line;

	while (get_next_line(fd, &line))
	{
		if (line[0] == 'R')
			parse_screen(game, line, 1);
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
			parse_floor_cell(game, line, 0);
		else if (line[0] == 'C' && line[1] == ' ')
			parse_floor_cell(game, line, 1);
		else if (game->flag_parse == 8)
			ft_lstadd_back(&elem, ft_lstnew((void *)line));
	}
	return (elem);
}

void	parse(t_game *game, char *argv)
{
	int		fd;
	int		i;
	t_list	*elem;
	int		x;

	if (!ft_strstr(argv, ".cub"))
		error(game, "Name file error", 0);
	elem = NULL;
	x = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		error(game, "error open file", 0);
	elem = parse_infos(game, fd, elem);
	i = ft_lstsize(elem);
	game->map_size = i;
	game->map = ft_calloc(i, sizeof(char *));
	while (elem)
	{
		game->map[x] = ft_strdup(elem->content);
		elem = elem->next;
		x++;
	}
	check_map(game, i);
	close(fd);
}
