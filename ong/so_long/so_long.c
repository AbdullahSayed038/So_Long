#include "so_long.h"

void	draw_map(m_lst *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->map_height)
	{
		j = 0;
		while (j < map->map_width)
		{
			if (map->map[i][j] == '1')
				mlx_put_image_to_window(map->mlx, map->win, map->wall_img , \
					j * map->img_width, i * map->img_height);
			else
				mlx_put_image_to_window(map->mlx, map->win, map->ground_img , \
					j * map->img_width, i * map->img_height);
			if (map->map[i][j] == 'P')
				mlx_put_image_to_window(map->mlx, map->win, map->player_img , \
					j * map->p_width + 115, i * map->p_height);
			j++;
		}
		i++;
	}
}

void	loadmap(m_lst *map, char **av)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: Unable to open file\n");
		// exitfree(1);
	}
	map->map = (char **)malloc(sizeof(char *) * (map->map_height + 1));
	while ((line = get_next_line(fd)) != NULL)
	{
		map->map[i] = line;
		i++;
	}
	map->map[i] = NULL;
	close(fd);
}

void initialize_images(m_lst *data)
{
	data->wall_img = mlx_xpm_file_to_image(data->mlx, "textures/wall.xpm", &data->img_width, &data->img_height);
	if (!data->wall_img)
	{
		ft_printf("Error: Unable to load wall image\n");
		exit(1);
	}
	data->ground_img = mlx_xpm_file_to_image(data->mlx, "textures/background.xpm", &data->img_width, &data->img_height);
	if (!data->ground_img)
	{
		ft_printf("Error: Unable to load ground image\n");
		// exitfree(1);
	}
	data->player_img = mlx_xpm_file_to_image(data->mlx, "textures/image-copy.xpm", &data->p_width, &data->p_height);
	if (!data->player_img)
	{
		ft_printf("Error: Unable to load player image\n");
		// exitfree(1);
	}
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
		data->player_img -= speed;
	else if(keycode == RIGHT || keycode == D)
		data->player_img += speed;
	else if(keycode == UP || keycode == W)
		data->player_img -= speed;
	else if(keycode == DOWN || keycode == S)
		data->player_img += speed;
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->mlx, data->player_img, data->, data->img_y);
	return (0);
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

void	get_map_dimensions(m_lst *data, char **av)
{
	int fd = open(av[1], O_RDONLY);
	char *line;
	int width;
	int height;
	int valid;

	valid = -1;
	width = 0;
	height = 0;
	if (fd < 0)
	{
		ft_printf("Error: Unable to open map file\n");
		// exitfree(1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		if (width == 0)
			width = ft_strlen(line);
		height++;
		if (ft_strchr(line, 'P') != NULL)
		{
			if (valid == 1)
			{
				ft_printf("Invalid Map");
				exit(1);
			}
			valid = 1;
		}
		free(line);
	}
	close(fd);
	data->map_width = width;
	data->map_height = height;
	ft_printf("Map width: %d, Map height: %d\n", data->map_width, data->map_height);
}


int main(int ac, char **av)
{
	m_lst	data;
	(void)ac;
	data.img_width = 64;
	data.img_height = 64;

	data.mlx = mlx_init();
	get_map_dimensions(&data, av);
	data.win = mlx_new_window(data.mlx, (data.map_width * data.img_width) - 64,  data.map_height * data.img_height, "so_long");
	loadmap(&data, av);
	initialize_images(&data);
	draw_map(&data);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 4, 1L, mouse_click, &data);
	mlx_loop(data.mlx);
	return (0);
}