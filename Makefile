NAME =  cub3d

SRC_DIR = srcs
PARSER_DIR = srcs/parsing

SRC  =	$(SRC_DIR)/main.c $(SRC_DIR)/raycasting.c $(SRC_DIR)/init.c \
		$(SRC_DIR)/player.c $(SRC_DIR)/parsing.c $(SRC_DIR)/utils.c \
		$(SRC_DIR)/moves.c $(SRC_DIR)/drawing.c

PARSER_SRC =	$(PARSER_DIR)/map_util.c $(PARSER_DIR)/parser_util.c \
				$(PARSER_DIR)/parser_util1.c $(PARSER_DIR)/parser_util2.c \
				$(PARSER_DIR)/parser_util3.c $(PARSER_DIR)/parser.c

ALL_SRCS = $(SRC) $(PARSER_SRC)

OBJ_DIR = obj

LIBFT_DIR = includes/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

MLX_DIR =includes/minilibx_opengl_20191021
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_INC = -I$(MLX_DIR) 
FRAMEWORK = -framework OpenGL -framework AppKit


CC = cc 
CFLAGS = -Wall -Wextra -Werror #-g


OBJ = $(ALL_SRCS:%.c=$(OBJ_DIR)/%.o)

RM = rm -f

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	@echo "Compiling libft..."
	@make -C $(MLX_DIR)
	@echo "Compiling $(NAME)..."
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(MLX_LIB) $(FRAMEWORK) -o $@
	@echo "$(NAME) compiled successfully!"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	$(RM) $(OBJ)
	@echo "Object files cleaned."

fclean: clean
	@make -C $(LIBFT_DIR) fclean


	$(RM) $(NAME)
	@echo "$(NAME) and libft cleaned."

re: fclean all
.PHONY: all clean fclean re