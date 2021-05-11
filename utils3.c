#include "cub3d.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*s1_cpy;
	int		i;

	i = 0;
	s1_cpy = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (s1_cpy == 0)
		return (0);
	while (s1[i])
	{
		s1_cpy[i] = s1[i];
		i++;
	}
	s1_cpy[i] = '\0';
	return (s1_cpy);
}

void	cell_or_floor(t_game *game, int type)
{	
	int	r;
	int	g;
	int	b;

	r = ft_atoi(game->buff);
	g = ft_atoi(game->buff2);
	b = ft_atoi(game->buff3);
	if (r > 255 || g > 255 || b > 255)
		error(game, "color error");
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

void free_array(char *array)
{
	if (!array)
		return ;
	free(array);
}

void free_matriz(char **matriz)
{
	int i;

	i = 0;
	while (matriz)
	{
		if (!matriz[i])
			return ;
		free(matriz[i]);
		i++;
	}
	if (!matriz)
		return ;
	free(matriz);
}