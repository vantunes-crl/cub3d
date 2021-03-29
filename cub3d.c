#include "mlx/mlx.h"
#include "cub3d.h"

typedef struct s_param{
	int		x;
	int		y;
	char	str[3];
}				t_param;

int				key_press(int keycode, t_param *param)
{
	static int a = 0;

	if (keycode == KEY_W)//Action when W key pressed
		param->x++;
	else if (keycode == KEY_S) //Action when S key pressed
		param->x--;
	printf("x: %d\n", param->x);
	return (0);
}

int             main(void)
{
    void    *mlx;
    void    *mlx_win;
	int		y;
	int		x;
	t_param		param;

	y = 50;
	mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	while (y < 150)
	{
		x = 50;
		while (x < 150)
		{
			mlx_pixel_put(mlx,mlx_win,x,y,0x00FFF000);
			x++;
		}
	y++;
	}
	mlx_hook(mlx_win, X_EVENT_KEY_PRESS, 0, &key_press, &param);
    mlx_loop(mlx);
}