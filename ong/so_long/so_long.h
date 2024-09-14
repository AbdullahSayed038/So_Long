#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# define HIGHT 600
# define WIDTH 800

# define A 0
# define S 1
# define D 2
# define W 13
# define RIGHT 124
# define LEFT 123
# define UP 126
# define DOWN 125
# define ESC 53
# define SPACE 49

typedef struct m_data
{
    void *mlx;
    void *win;
    void *wall_img;      // Image for walls
    void *ground_img;    // Image for ground
	void *player_img;    // Image for player
	void *collect_img;
	void *exit_img;
	void *door_img;
    char **map;          // 2D array to hold the map
	char **map_copy;
    int map_width;       // Width of the map
    int map_height;      // Height of the map
    int img_width;       // Width of images (wall and ground)
    int img_height;      // Height of images (wall and ground)
	int p_height;
	int p_width;
	int x;
	int y;
	int dx;
	int dy;
	int collect;
} m_lst;

#endif