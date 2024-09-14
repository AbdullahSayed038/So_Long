#include "so_long.h"

int close_window(void *param)
{
	m_lst	*mlx;

	mlx = param;
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	// free(mlx);

	exit (0);
	return (0);
}

void	draw_map(m_lst *map)
{
	int	i;
	int	j;

	i = 0;
	map->collect = 0;
	while (i < map->map_height)
	{
		j = 0;
		while (j < map->map_width)
		{
			if (map->map[i][j] == '1')
				mlx_put_image_to_window(map->mlx, map->win, map->wall_img , \
					j * map->img_width, i * map->img_height);
			else if (map->map[i][j] == '0')
				mlx_put_image_to_window(map->mlx, map->win, map->ground_img , \
					j * map->img_width, i * map->img_height);
			// else
			// 	exit(1);
			if (map->map[i][j] == 'P')
			{
				map->x = j;
				map->y = i;
				mlx_put_image_to_window(map->mlx, map->win, map->ground_img , \
					j * map->img_width, i * map->img_height);
				mlx_put_image_to_window(map->mlx, map->win, map->player_img , \
				(j * 64), i * 64);
			}
			else if (map->map[i][j] == 'C')
			{
				mlx_put_image_to_window(map->mlx, map->win, map->ground_img , \
					j * map->img_width, i * map->img_height);
				mlx_put_image_to_window(map->mlx, map->win, map->collect_img , \
				j * 64, i * 64);
				map->collect++;
			}
			else if (map->map[i][j] == 'E')
			{
				mlx_put_image_to_window(map->mlx, map->win, map->ground_img , \
					j * map->img_width, i * map->img_height);
				map->dx = j;
				map->dy = i;
				mlx_put_image_to_window(map->mlx, map->win, map->door_img , \
				j * 64, i * map->p_height);
			}
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
	data->collect_img = mlx_xpm_file_to_image(data->mlx, "textures/redball.xpm", &data->img_width, &data->img_height);
	if (!data->player_img)
	{
		ft_printf("Error: Unable to load player image\n");
		// exitfree(1);
	}
	data->exit_img = mlx_xpm_file_to_image(data->mlx, "textures/open.xpm", &data->img_width, &data->img_height);
	if (!data->player_img)
	{
		ft_printf("Error: Unable to load player image\n");
		// exitfree(1);
	}
	data->door_img = mlx_xpm_file_to_image(data->mlx, "textures/closed.xpm", &data->img_width, &data->img_height);
	if (!data->player_img)
	{
		ft_printf("Error: Unable to load player image\n");
		// exitfree(1);
	}
}

void	move(m_lst *data, int new_x, int new_y)
{
	if (data->map[new_y][new_x] == '1')
		return ;
	if (data->map[new_y][new_x] == '0')
	{
		mlx_put_image_to_window(data->mlx, data->win, data->ground_img, (data->x) * 64, (data->y) * 64);
		mlx_put_image_to_window(data->mlx, data->win, data->player_img, (new_x) * 64, (new_y) * 64);
		if (data->map[data->y][data->x] == 'E')
			mlx_put_image_to_window(data->mlx, data->win, data->door_img, (data->dx) * 64, (data->dy) * 64);
		else
			data->map[data->y][data->x] = '0';
		data->map[new_y][new_x] = 'P';
	}
	if (data->map[new_y][new_x] == 'C')
	{
		mlx_put_image_to_window(data->mlx, data->win, data->ground_img, (data->x) * 64, (data->y) * 64);
		mlx_put_image_to_window(data->mlx, data->win, data->ground_img, (new_x) * 64, (new_y) * 64);
		mlx_put_image_to_window(data->mlx, data->win, data->player_img, (new_x) * 64, (new_y) * 64);
		if (data->map[data->y][data->x] == 'E')
			mlx_put_image_to_window(data->mlx, data->win, data->door_img, (data->dx) * 64, (data->dy) * 64);
		data->map[data->y][data->x] = '0';
		data->map[new_y][new_x] = 'P';
		data->collect--;
	}
	if (data->collect == 0)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->exit_img, (data->dx) * 64, (data->dy) * 64);
	}
	if (data->map[new_y][new_x] == 'E')
	{
		mlx_put_image_to_window(data->mlx, data->win, data->ground_img, (data->x) * 64, (data->y) * 64);
		mlx_put_image_to_window(data->mlx, data->win, data->player_img, (new_x) * 64, (new_y) * 64);
		data->map[data->y][data->x] = '0';
		if (data->collect == 0)
			exit(0);
	}
	data->x = new_x;
	data->y = new_y;
	
}

int key_press(int keycode, void *param)
{
	m_lst	*data;
	int		speed;

	speed = 64;
	data = (m_lst *)param;
	ft_printf("KEY:   %d\n\n\n", keycode);
	if (keycode == ESC)
		close_window(param);
	else if(keycode == LEFT || keycode == A)
		move(data, (data->x) - 1, data->y);
	else if(keycode == RIGHT || keycode == D)
		move(data, (data->x) + 1, data->y);
	else if(keycode == UP || keycode == W)
		move(data, data->x, (data->y) - 1);
	else if(keycode == DOWN || keycode == S)
		move(data, data->x, (data->y) + 1);
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

void checkborder(char **str)
{
	int i = 0;
	int j = 1;
	while (str[0][i] != '\n')
	{
		if (str[0][i] != '1')
			exit(1);
		i++;
	}
	i--;
	while (str[j])
	{
		if (str[j][0] == '1' && str[j][i] == '1')
			j++;
		else
			exit(1);
	}
	j--;
	i = 0;
	while (str[j][i] != '\0')
	{
		if (str[j][i] != '1')
			exit(1);
		i++;
	}
	return ;
}

void checkmap(m_lst *data)
{
	int i = 0;
	int j = 0;
	int p = 0;
	int e = 0;
	int c = 0;
	checkborder(data->map);
	while(data->map[j])
	{
		i = 0;
		while(data->map[j][i])
		{
			if (data->map[j][i] == 'P')
				p++;
			if (data->map[j][i] == 'E')
				e++;
			if (data->map[j][i] == 'C')
				c++;
			i++;
		}
		j++;
	}
	if (p == 1 && e == 1 && c > 0)
		return ;
	else
		exit(1);
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
	checkmap(&data);
	draw_map(&data);
	mlx_hook(data.win, 2, 0, key_press, &data);
	mlx_hook(data.win, 4, 0, mouse_click, &data);
	mlx_loop(data.mlx);
	return (0);
}