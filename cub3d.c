#include "mlx/mlx.h"
#include "cub3d.h"

# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

typedef struct s_vars
{
	void 	*mlx;
	void 	*win;
	void	*img;
	float y;
	float x;

}	t_vars;

void	draw_square(t_vars *vars, int size, int color) //funcao para formar uma quadrado de pixeis
{
	int		x;
	int		y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			mlx_pixel_put(vars->mlx, vars->win, x + vars->x, y + vars->y, color);
			x++;
		}
		y++;
	}
}

int key_press(int keycode, t_vars *var) //move keys
{
	if (keycode == KEY_A)
	{
		draw_square(var, 50, 0x000000);
		var->x-=10; //esquerda
		draw_square(var, 50, 0x00FF0000);
	}
	else if (keycode == KEY_D)
	{	
		draw_square(var,50,0x000000);
		var->x+=10; // direita
		draw_square(var,50,0x00FF00);
	}
	else if (keycode == KEY_W)
	{
		draw_square(var,50,0x000000);
		var->y-=10; // baixo
		draw_square(var,50,0xFFFFFF);
	}
	else if (keycode == KEY_S)
	{
		draw_square(var,50,0x000000);
		var->y+=10; //cima
		draw_square(var,50,0x0000FF);
	}
	return (0);
}

int main()
{
	t_vars	var;
	float py,px; //player

	int img_width;
	int img_height;

	var.x = 500; //incial position
	var.y = 500; // inicial position
	var.mlx = mlx_init();
    var.win = mlx_new_window(var.mlx, 1000, 1000, "cubd3");
	var.img = mlx_xpm_file_to_image(var.mlx, "./textures/wall_n.xpm", &img_width, &img_height);
	mlx_hook(var.win, 2, 1L<<0,key_press, &var);
    mlx_loop(var.mlx);
}