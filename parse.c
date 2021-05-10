#include "cub3d.h"

void	chose_side(t_game *game, int side, char *texture)
{
	if (side == 0)
		game->tex_north = ft_strdup(texture);
	if (side == 1)
		game->tex_south = ft_strdup(texture);
	if (side == 2)
		game->tex_east = ft_strdup(texture);
	if (side == 3)
		game->tex_west = ft_strdup(texture);
	if (side == 4)
		game->tex_sprite = ft_strdup(texture);
	game->flag_parse += 1;
}

void	check_left_borders(t_game *game, int x, int j)
{
	int	k;

	if (!(ismap(game->map[x][j])))
		error("Map");
	if (game->map[x][j] == ' ')
	{
		k = 0;
		while (game->map[x][k] == ' ')
			k++;
		if (game->map[x][k] != '1')
			error("Map");
	}
}

void	check_right_borders(t_game *game, int x, int j)
{
	int	k;

	if (!(ismap(game->map[x][j])))
		error("Map");
	if (game->map[x][j] == ' ')
	{
		k = j;
		while (game->map[x][k] == ' ')
			k--;
		if (game->map[x][k] != '1')
			error("Map");
	}
}

void	check_top_botton(t_game *game, int x, int j)
{
	if ((game->map[x][j] == ' ' && game->map[x][j - 1] == '0') || (game->map[x][j] == ' ' && game->map[x][j + 1] == '0'))
		error("space in map");
	if ((game->map[x][j] == '0' && !game->map[x - 1][j])
		|| (game->map[x][j] == '0' && game->map[x - 1][j] == ' '))
		error("Map");
	else if ((game->map[x][j] == '0' && !game->map[x + 1][j])
		|| (game->map[x][j] == '0' && game->map[x + 1][j] == ' '))
		error("Map");
	if ((game->map[x][j] == '2' && !game->map[x - 1][j])
		|| (game->map[x][j] == '2' && game->map[x - 1][j] == ' '))
		error("Map");
	else if ((game->map[x][j] == '2' && !game->map[x + 1][j])
		|| (game->map[x][j] == '2' && game->map[x + 1][j] == ' '))
		error("Map");
}

int	check_start_map(t_game *game)
{
	int	x;

	x = 0;
	while (!ismap(game->map[x][0]))
		x++;
	return (x);
}

void	check_map(t_game *game, int size_map)
{
	int	x;
	int	j;

	x = 0;
	j = 0;
	if (game->flag_parse != 8)
		error("Need more arguments in parse file");
	while (x < size_map)
	{
		j = 0;
		while (j < ft_strlen(game->map[x]))
		{
			if (x == check_start_map(game) || j == 0)
				check_left_borders(game, x, j);
			else if ((x == size_map - 1)
				|| (j + 1 == ft_strlen(game->map[x])))
				check_right_borders(game, x, j);
			else if (!((x == size_map - 1
						|| j + 1 == ft_strlen(game->map[x]))
					|| (x == check_start_map(game) || j == 0)))
				check_top_botton(game, x, j);
			j++;
		}
		x++;
	}
}
