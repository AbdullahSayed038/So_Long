NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -framework OpenGL -framework AppKit
SRC = so_long.c
OBJ = $(SRC:.c=.o)
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
MLX_DIR = minilibx/
MLX = $(MLX_DIR)libmlx.a

all			:	print_art $(NAME)

%.o			:	%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@make -C $(MLX_DIR)

$(NAME)	:	$(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(LIBFT) $(MLX) $^ -o $@

clean		:
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean		:	clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re			:	fclean all

print_art	:
	@echo "                                                      "
	@echo "       ███████████                 ██████████        "
	@echo "    ████          ███            ███         ███     "
	@echo "   ██               ██         ██              ██    "
	@echo "  ██    █████████    ██       ██    ████████    ██   "
	@echo "  ██   ██       ██    ██     ██   ███       ██   ██  "
	@echo " ██   ██          █    ████████   █          █    ██ "
	@echo " ██   ██        ███               ███        █    ██ "
	@echo "  █    ██    ████████                ██     ██    █  "
	@echo "  ██    ████████████████     ████████████████    ██  "
	@echo "   ██     ████   ████  ██  ███   ███   ███      ██   "
	@echo "     ███  ██     ███     ███    ████    ███   ██     "
	@echo "        ████     ███     ███    ████     ████        "
	@echo "        ████    █████    ███    █████    ███         "
	@echo "        ██ ██   █████   ████    █████   ██ █         "
	@echo "        █   ██  ████   ██   ██  ████  ███  ██        "
	@echo "        ██    █████████       █████████    ██        "
	@echo "        ████████████████████████████████████         "
	@echo "         ██  ██ █    ███     ██     █ █   ██         "
	@echo "          ████  █   █  █     ███   █   ██ █          "
	@echo "           ██   ██ ██  ██   █  ██ ██    ██           "
	@echo "            ███  █ █    ██ ██   ████   ██            "
	@echo "              ██ ██      █ █    ███  ██              "
	@echo "                ████     ███     ████                "
	@echo "                    █████████████                    "
	@echo "                                                     "


PHONY: all clean fclean re print_art