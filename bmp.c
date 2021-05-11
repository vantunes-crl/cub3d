#include "cub3d.h"

void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

int	write_bmp_header(int fd, int filesize, t_game *game)
{
	int				i;
	int				tmp;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(54);
	bmpfileheader[14] = (unsigned char)(40);
	tmp = game->width_screen;
	set_int_in_char(bmpfileheader + 18, tmp);
	tmp = game->height_screen;
	set_int_in_char(bmpfileheader + 22, tmp);
	bmpfileheader[27] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	return (!(write(fd, bmpfileheader, 54) < 0));
}

int	write_bmp_data(int file, t_game *game)
{
	int					i;
	int					j;

	i = game->height_screen - 1;
	draw_all(game);
	while (i >= 0)
	{
		j = 0;
		while (j < game->width_screen)
		{
			write(file, &game->bmp_buf[i][j], 3);
			j++;
		}
		i--;
	}
	return (1);
}

void	creat_bmp(t_game *game)
{
	int	fd;
	int	fz;
	int	i;

	i = 0;
	init_bpm_buf(game);
	fz = 54 + (3 * (game->height_screen * game->width_screen));
	calc(game);
	draw(game);
	draw_rectangles(game);
	fd = open("screenshot.bmp", O_WRONLY | O_CREAT, 0777 | O_TRUNC | O_APPEND);
	write_bmp_header(fd, fz, game);
	write_bmp_data(fd, game);
	while (i++ < game->height_screen)
		free(game->bmp_buf[i]);
	free(game->bmp_buf);
	close(0);
	exit(0);
}

void	init_bpm_buf(t_game *game)
{
	int	i;

	i = 0;
	game->bmp_buf = ft_calloc(game->height_screen, sizeof(int *));
	while (i < game->height_screen)
	{
		game->bmp_buf[i] = ft_calloc(game->width_screen, sizeof(int *));
		i++;
	}
}
