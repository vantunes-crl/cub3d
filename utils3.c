#include "cub3d.h"

void	cell_or_floor(t_game *game, int type)
{	
	int	r;
	int	g;
	int	b;

	r = ft_atoi(game->buff);
	g = ft_atoi(game->buff2);
	b = ft_atoi(game->buff3);
	if (r > 255 || g > 255 || b > 255)
		error(game, "color error", 0);
	if (type == 0)
		game->floor_color = create_trgb(r, g, b);
	else if (type == 1)
		game->cell_color = create_trgb(r, g, b);
	game->flag_parse += 1;
}

int	check_start_map(t_game *game)
{
	int	x;

	x = 0;
	while (!ismap(game->map[x][0]))
		x++;
	return (x);
}

int	ismap(char c)
{
	if (c == ' ' || c == '1')
		return (1);
	return (0);
}

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_size)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}

void	free_buffs(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 5)
		free(game->texture[i]);
	free(game->texture);
	free(game->zBuffer);
	i = -1;
	while (++i < game->height_screen)
		free(game->buf[i]);
	free(game->buf);
}
