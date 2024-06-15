# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 16:31:23 by dcaro-ro          #+#    #+#              #
#    Updated: 2024/06/04 19:27:22 by dcaro-ro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER = server
NAME_CLIENT = client
NAME_SERVER_BONUS = server_bonus
NAME_CLIENT_BONUS = client_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
OBJ_DIR = obj

SRCS_SERVER = $(SRC_DIR)/server.c
SRCS_CLIENT = $(SRC_DIR)/client.c
SRCS_SERVER_BONUS = $(SRC_DIR)/server_bonus.c
SRCS_CLIENT_BONUS = $(SRC_DIR)/client_bonus.c

OBJS_SERVER = $(OBJ_DIR)/server.o
OBJS_CLIENT = $(OBJ_DIR)/client.o
OBJS_SERVER_BONUS = $(OBJ_DIR)/server_bonus.o
OBJS_CLIENT_BONUS = $(OBJ_DIR)/client_bonus.o

all: $(LIBFT) $(NAME_SERVER) $(NAME_CLIENT)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJS_SERVER) $(LIBFT)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT) $(LIBFT)

bonus: $(LIBFT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(NAME_SERVER_BONUS): $(OBJS_SERVER_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_SERVER_BONUS) $(OBJS_SERVER_BONUS) $(LIBFT)

$(NAME_CLIENT_BONUS): $(OBJS_CLIENT_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT_BONUS) $(OBJS_CLIENT_BONUS) $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
