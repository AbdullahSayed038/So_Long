#include "minilibx/mlx.h"
#include <stdlib.h>

#define HIGHT 2000
#define WIDTH 1000

int main()
{
	void	*mlx_ptr;
	void	*mlx_win;
	int x;
	int y;

	mlx_ptr = mlx_init();	
	mlx_win = mlx_new_window(mlx_ptr, WIDTH, HIGHT, "cool");
	x = 0;
	while(x < WIDTH)
	{
		y = 0;
		while (y < HIGHT)
		{
			mlx_pixel_put(mlx_ptr, mlx_win, x, y, rand() % 0x1000000);
			y++;
		}
		x++;
	}
	mlx_loop(mlx_ptr);
}
