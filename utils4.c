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

int	exit_game(t_game *game)
{
	free_map(game);
	free_buffs(game);
	exit(0);
}

void	need_screenshot(t_game *game, char *argv)
{
	if (ft_strncmp(argv, "--save", ft_strlen(argv)) == 0)
		game->screenshot = 1;
	else
		error(game, "invalid argument", 0);
}
