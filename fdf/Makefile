# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/15 15:25:13 by dcaro-ro          #+#    #+#              #
#    Updated: 2024/06/27 14:30:32 by dcaro-ro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME							=	fdf

SRC_DIR							=   src
OBJ_DIR							=	obj
INCLUDE_DIR						=	include
LIB_DIR							=	lib

SRCS							=	$(SRC_DIR)/fdf.c \
									$(SRC_DIR)/hooks/fdf_hooks.c \
									$(SRC_DIR)/rendering/fdf_init.c \
									$(SRC_DIR)/rendering/fdf_project.c \
									$(SRC_DIR)/rendering/fdf_draw.c \
									$(SRC_DIR)/rendering/fdf_render.c \
									$(SRC_DIR)/parsing/fdf_parsing_utils.c \
									$(SRC_DIR)/parsing/fdf_read_lines.c \
									$(SRC_DIR)/parsing/fdf_fill_map.c \
									$(SRC_DIR)/parsing/fdf_get_map.c \
									$(SRC_DIR)/utils/fdf_cleanup.c \
									$(SRC_DIR)/utils/fdf_utils.c

OBJS							=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR						=	$(LIB_DIR)/libft
LIBFT							=	$(LIBFT_DIR)/libft.a
MLX_DIR							=	$(LIB_DIR)/minilibx-linux
MLX								=	$(MLX_DIR)/libmlx_Linux.a

CC								=	gcc
CFLAGS							=	-Wall -Wextra -Werror
LDFLAGS							=	-L$(MLX_DIR) -L$(LIBFT_DIR)
MLX_FLAGS						=	-lmlx -lXext -lX11 -lm -lz

INCLUDES						=	-I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# Default target
all: $(NAME)

# Link the final executable
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) $(LDFLAGS) -o $(NAME)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile the libft library
$(LIBFT):
	make -C $(LIBFT_DIR)

# Compile the mlx library
$(MLX):
	make -C $(MLX_DIR)

# Clean object files
clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

# Clean object files and the executable
fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

# Recompile everything
re: fclean all

.PHONY: all clean fclean re
