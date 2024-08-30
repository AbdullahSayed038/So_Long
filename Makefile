NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = so_long.c
OBJ = $(SRC:.c=.o)

mlx = libmlx.a -framework OpenGL -framework AppKit
libft = libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(mlx) $(libft)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
