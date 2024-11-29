# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/06 16:15:55 by dcaro-ro          #+#    #+#              #
#    Updated: 2024/10/13 03:53:37 by dcaro-ro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror

SRC_DIR			=	src
OBJ_DIR			=	obj
INCLUDE_DIR		=	include

SRCS			=	$(SRC_DIR)/philo.c \
					$(SRC_DIR)/utils/philo_utils.c \
					$(SRC_DIR)/utils/mutex_utils.c \
					$(SRC_DIR)/utils/sim_utils.c \
					$(SRC_DIR)/philo_table.c \
					$(SRC_DIR)/init_simulation.c \

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
