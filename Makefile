# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/19 08:35:50 by dcaro-ro          #+#    #+#              #
#    Updated: 2023/10/19 12:02:51 by dcaro-ro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		libft.a

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

#BONUS		=		ft_lstnew.c\
#					ft_lstadd_front.c\
#					ft_lstsize.c\
#					ft_lstlast.c\
#					ft_lstadd_back.c\
#					ft_lstdelone.c\
#					ft_lstclear.c\
#					ft_lstiter.c\
#					ft_lstmap.c\

OBJS		=		${SRCS:.c=.o}

#BONUS_OBJS	=		$(BONUS:.c=.o)

CC			=		gcc

CFLAGS		=		-Wall -Werror -Wextra

RM			=		rm -f

${NAME}:			$(OBJS)
							ar rcs $(NAME) $(OBJS)


%.o: 				%.c
						$(CC) -I. $(CFLAGS) -o $@ -c $?

all: 				${NAME}

clean:
					${RM} ${OBJS}

fclean:				clean
							${RM} ${NAME}

re:							fclean all

#bonus:						$(OBJS) $(BONUS_OBJS)
#									ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY:				all clean fclean re .c.o
