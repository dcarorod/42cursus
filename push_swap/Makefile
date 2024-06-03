NAME			=	push_swap

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

SRC_DIR			=	src
OBJ_DIR			=	obj
INCLUDE_DIR		=	include

SRCS			=	$(SRC_DIR)/push_swap.c \
					$(SRC_DIR)/operations/stack_ops.c \
					$(SRC_DIR)/operations/push.c \
					$(SRC_DIR)/operations/swap.c \
					$(SRC_DIR)/operations/rotate.c \
					$(SRC_DIR)/operations/reverse_rotate.c \
					$(SRC_DIR)/sorting/sort_small.c \
					$(SRC_DIR)/sorting/sort_large.c \
					$(SRC_DIR)/utils/maximum.c \
					$(SRC_DIR)/utils/minimum.c \
					$(SRC_DIR)/utils/parsing.c \
					$(SRC_DIR)/utils/push_swap_utils.c \
					$(SRC_DIR)/ft_atoi/ft_atoi.c \
					$(SRC_DIR)/ft_printf/ft_printf.c \
					$(SRC_DIR)/ft_printf/ft_printf_utils.c \
					$(SRC_DIR)/ft_printf/ft_handle_char.c \
					$(SRC_DIR)/ft_printf/ft_handle_hex.c \
					$(SRC_DIR)/ft_printf/ft_handle_int.c \
					$(SRC_DIR)/ft_printf/ft_handle_percent.c \
					$(SRC_DIR)/ft_printf/ft_handle_ptr.c \
					$(SRC_DIR)/ft_printf/ft_handle_specifier.c \
					$(SRC_DIR)/ft_printf/ft_handle_str.c \
					$(SRC_DIR)/ft_printf/ft_handle_uint.c

OBJS			=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
