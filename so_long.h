#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# define HEIGHT 600
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

typedef struct m_lst
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*img;
	int		img_x;
	int		img_y;
	int		img_width;
	int		img_height;
	void	*wall_img;
	void	*ground_img;
	int		mapwidth;
	int		mapheight;
	char	**map;
} m_lst;
#endif