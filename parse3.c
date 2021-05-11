#include "cub3d.h"

void	screen_error(t_game *game)
{
	if (game->width_screen > 2560)
		game->width_screen = 2560;
	if (game->height_screen > 1440)
		game->height_screen = 1440;
	if (!game->width_screen)
		error(game, "screen error", 0);
	if (!game->height_screen)
		error(game, "screen error", 0);
}

void	parse_screen(t_game *game, char *line, int i)
{
	char	width_screen[5];
	char	height_screen[5];
	int		j;

	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			while (line[i] >= '0' && line[i] <= '9')
				width_screen[j++] = line[i++];
			width_screen[j] = '\0';
			j = 0;
			i++;
			while (line[i] >= '0' && line[i] <= '9')
				height_screen[j++] = line[i++];
			height_screen[j] = '\0';
			break ;
		}
		i++;
	}
	game->width_screen = ft_atoi(width_screen);
	game->height_screen = ft_atoi(height_screen);
	screen_error(game);
	game->flag_parse += 1;
}

int	check_all_map(char c)
{
	if (c == ' ' || c == '1' || c == '2'
		|| c == '0' || c == 'N' || c == 'W' || c == 'S' || c == 'E')
		return (1);
	return (0);
}
