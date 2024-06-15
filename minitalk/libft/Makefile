# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 14:37:14 by dcaro-ro          #+#    #+#              #
#    Updated: 2024/06/02 14:37:15 by dcaro-ro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		libft.a

CC			=		gcc
CFLAGS		=		-Wall -Wextra -Werror

OBJ_DIR		=		obj
INCLUDE_DIR	=		include
PRINTF_DIR	=		ft_printf

SRCS		=		ft_isalpha.c\
					ft_isdigit.c\
					ft_isalnum.c\
					ft_isascii.c\
					ft_isprint.c\
					ft_strlen.c\
					ft_memset.c\
					ft_bzero.c\
					ft_memcpy.c\
					ft_memmove.c\
					ft_strlcpy.c\
					ft_strlcat.c\
					ft_toupper.c\
					ft_tolower.c\
					ft_strchr.c\
					ft_strrchr.c\
					ft_strncmp.c\
					ft_memchr.c\
					ft_memcmp.c\
					ft_strnstr.c\
					ft_atoi.c\
					ft_calloc.c\
					ft_strdup.c\
					ft_substr.c\
					ft_strjoin.c\
					ft_strtrim.c\
					ft_split.c\
					ft_itoa.c\
					ft_strmapi.c\
					ft_striteri.c\
					ft_putchar_fd.c\
					ft_putstr_fd.c\
					ft_putendl_fd.c\
					ft_putnbr_fd.c\
					ft_lstnew.c\
					ft_lstadd_front.c\
					ft_lstsize.c\
					ft_lstlast.c\
					ft_lstadd_back.c\
					ft_lstdelone.c\
					ft_lstclear.c\
					ft_lstiter.c\
					ft_lstmap.c\
					$(PRINTF_DIR)/ft_printf.c\
					$(PRINTF_DIR)/ft_printf_utils.c\
					$(PRINTF_DIR)/ft_handle_specifier.c\
					$(PRINTF_DIR)/ft_handle_char.c\
					$(PRINTF_DIR)/ft_handle_str.c\
					$(PRINTF_DIR)/ft_handle_int.c\
					$(PRINTF_DIR)/ft_handle_uint.c\
					$(PRINTF_DIR)/ft_handle_hex.c\
					$(PRINTF_DIR)/ft_handle_ptr.c\
					$(PRINTF_DIR)/ft_handle_percent.c\

OBJS			=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
