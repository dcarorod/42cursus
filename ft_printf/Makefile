# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 14:19:40 by dcaro-ro          #+#    #+#              #
#    Updated: 2023/11/01 11:25:03 by dcaro-ro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libftprintf.a

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

SRC_DIR			=	src

INCLUDE_DIR		=	include

LIB_DIR			=	.

SRCS			=	$(SRC_DIR)/ft_printf.c \
					$(SRC_DIR)/utils/ft_printf_utils.c \
					$(SRC_DIR)/format_handlers/ft_handle_char.c \
					$(SRC_DIR)/format_handlers/ft_handle_hex.c \
					$(SRC_DIR)/format_handlers/ft_handle_int.c \
					$(SRC_DIR)/format_handlers/ft_handle_percent.c \
					$(SRC_DIR)/format_handlers/ft_handle_ptr.c \
					$(SRC_DIR)/format_handlers/ft_handle_specifier.c \
					$(SRC_DIR)/format_handlers/ft_handle_str.c \
					$(SRC_DIR)/format_handlers/ft_handle_uint.c

OBJS			=	$(SRCS:.c=.o)

all:				$(NAME)

$(NAME):			$(OBJS)
							ar rc $(NAME) $(OBJS)
							ranlib $(NAME)

%.o:				$(SRC_DIR)/%.c
									$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
					rm -f $(OBJS)

fclean:				clean
							rm -f $(NAME)
							rm -f $(OBJS)

re:					fclean all

.PHONY:				all clean fclean re
