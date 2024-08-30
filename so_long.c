#include "so_long.h"

void *load_image(void *mlx, char *filename, int *wid, int *hei)
{
	void *img;
	img = mlx_xpm_file_to_image(mlx, filename, wid, hei);
	return (img);
}

int close_window(void *param)
{
	m_lst	*mlx;

	mlx = param;
	if (mlx->mlx_win)
		mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	free(mlx);

	exit (0);
	return (0);
}

int key_press(int keycode, void *param)
{
	m_lst	*data;
	int		speed;

	speed = 64;
	data = (m_lst *)param;
	if (keycode == ESC)
		close_window(param);
	else if(keycode == LEFT || keycode == A)
		data->img_x -= speed;
	else if(keycode == RIGHT || keycode == D)
		data->img_x += speed;
	else if(keycode == UP || keycode == W)
		data->img_y -= speed;
	else if(keycode == DOWN || keycode == S)
		data->img_y += speed;
	mlx_clear_window(data->mlx_ptr, data->mlx_win);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, data->img_x, data->img_y);
	return (0);
}
void draw_map(m_lst *data)
{
    int i, j;
    for (i = 0; i < 800; i++)
    {
        for (j = 0; j < 600; j++)
        {
            if (data->map[i][j] == '1') // Wall
                mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->wall_img, j * 64, i * 64);
            else if (data->map[i][j] == '0') // Ground
                mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->ground_img, j * 64, i * 64);
            // Add other cases for collectibles, exits, etc.
        }
    }
}


int mouse_click(int button, int x, int y, void *param)
{
	(void)param;
	if (button == 1)
	{
		ft_printf("You are clicking at (%d,%d)\n", x, y);
	}

	return (0);
}

int main()
{
	m_lst	data;
	int		img_width;
	int		img_height;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.mlx_win = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "so_long");
	data.img = load_image(data.mlx_ptr, "vertopal.com_zombie.xpm", &img_width, &img_height);
	data.wall_img = load_image(data.mlx_ptr, "StoneWallStandard.xpm", &img_width, &img_height);
	if (!data.wall_img)
    {
        ft_printf("Failed to load wall image\n");
        return (1);
    }
	data.ground_img = load_image(data.mlx_ptr, "StoneWallBackground.xpm", &img_width, &img_height);
	if (!data.ground_img)
    {
        ft_printf("Failed to load ground image\n");
        return (1);
    }
	if (!data.img)
		return(1);
	data.img_width = img_width;
	data.img_height = img_height;
	data.img_x = (800 - data.img_width) / 2;
	data.img_y = (600 - data.img_height) / 2;
	draw_map(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, data.img, data.img_x, data.img_y);
	mlx_hook(data.mlx_win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx_win, 17, 0L, close_window, &data);
	// mlx_hook(data.mlx_win, 4, 1L, mouse_click, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_window(data.mlx_ptr, data.mlx_win);
	free(data.mlx_ptr);
	return(0);
}
//so we use event 2 for button press
// 4 for mouse
// 17 for i think control c
// 6 for mouse movement but we wouldnt need