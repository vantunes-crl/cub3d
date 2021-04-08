#include "cub3d.h"

void	calc(t_info *info , t_flor flor)
{
	t_cell cell;
	t_wall wall;
	t_textures textures;

	flor.y = 0;
	while(flor.y < height)
	{
		flor = put_flor(flor,info);
		cell.x = 0;
		while (++cell.x < width)
			cell = put_cell(info,&flor, cell);
		flor.y++;
	}
	wall.x = 0;
	while (++wall.x < width)
	{
		init_wall(&wall,info);
		steps(&wall, info);
		perp_wall(info, &wall);
		textures_wall(&wall,&textures,info);
		draw_wall(info,&textures, &wall);
		floor_wall(&wall, &textures);
		flor_wall2(info,&textures,&wall,&flor);
	}
}

int	main_loop(t_info *info)
{
	t_flor flor;

	calc(info, flor);
	draw(info);
	return (0);
}

int init_buff(t_info *info)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			info->buf[i][j] = 0;
		}
	}

	if (!(info->texture = (int **)malloc(sizeof(int *) * 8)))
		return (-1);
	for (int i = 0; i < 8; i++)
	{
		if (!(info->texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			return (-1);
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < texHeight * texWidth; j++)
		{
			info->texture[i][j] = 0;
		}
	}
}

int	main(void)
{
	t_info info;
	
	info.mlx = mlx_init();
	init_buff(&info);
	init_map(&info);
	load_texture(&info);
	info.posX = 22.0;
	info.posY = 11.5;
	info.dirX = -1.0;
	info.dirY = 0.0;
	info.planeX = 0.0;
	info.planeY = 0.66;
	info.moveSpeed = 0.08;
	info.rotSpeed = 0.08;
	info.win = mlx_new_window(info.mlx, width, height, "mlx");
	info.img.img = mlx_new_image(info.mlx, width, height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS,1<<0L, &key_press, &info);
	mlx_loop(info.mlx);
}
