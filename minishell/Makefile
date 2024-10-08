# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/05 15:40:34 by dcaro-ro          #+#    #+#              #
#    Updated: 2024/10/02 15:23:20 by dcaro-ro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME							=	minishell

SRC_DIR							=   src
OBJ_DIR							=	obj
INCLUDE_DIR						=	include
LIBFT_DIR						=	libft
HASHMAP_DIR						=	$(SRC_DIR)/hashmap
LEXER_DIR						=	$(SRC_DIR)/lexer
PARSER_DIR						=	$(SRC_DIR)/parser
BUILTINS_DIR					=	$(SRC_DIR)/builtins
EXEC_DIR						=	$(SRC_DIR)/exec
UTILS_DIR						=	$(SRC_DIR)/utils
DEBUG_DIR						=	$(TEST_DIR)/debug
ENV_DIR							=	$(SRC_DIR)/env
SIGNALS_DIR						=	$(SRC_DIR)/signals

SRCS							=	$(SRC_DIR)/minishell.c \
									$(UTILS_DIR)/ms_print_utils.c \
									$(UTILS_DIR)/minishell_utils.c \
									$(HASHMAP_DIR)/hashmap_utils.c \
									$(HASHMAP_DIR)/hashmap_cleanup.c \
									$(HASHMAP_DIR)/hashmap_get.c \
									$(HASHMAP_DIR)/hashmap_remove.c \
									$(HASHMAP_DIR)/hashmap_insert.c \
									$(HASHMAP_DIR)/hashmap_init.c \
									$(HASHMAP_DIR)/hashmap_copy.c \
									$(HASHMAP_DIR)/hashmap_to_vault.c \
									$(HASHMAP_DIR)/vault_sort.c \
									$(HASHMAP_DIR)/vault_print.c \
									$(LEXER_DIR)/preprocess/preprocess_utils.c \
									$(LEXER_DIR)/preprocess/preprocess_input.c \
									$(LEXER_DIR)/lex_utils/lexer_str_utils.c \
									$(LEXER_DIR)/lex_utils/lexer_utils.c \
									$(LEXER_DIR)/lex_utils/segment_str.c \
									$(LEXER_DIR)/lex_utils/lexer_env_utils.c \
									$(LEXER_DIR)/token_utils.c \
									$(LEXER_DIR)/lexer_handle_quote.c \
									$(LEXER_DIR)/lexer_handle_assignment.c \
									$(LEXER_DIR)/lexer_expand_variables.c \
									$(LEXER_DIR)/lexer_handle_env.c \
									$(LEXER_DIR)/lexer_handle_word.c \
									$(LEXER_DIR)/lexer_special_char.c \
									$(LEXER_DIR)/lexer.c \
									$(PARSER_DIR)/parser_cleanup.c \
									$(PARSER_DIR)/parser_utils.c \
									$(PARSER_DIR)/parse_redir.c \
									$(PARSER_DIR)/parse_command.c \
									$(PARSER_DIR)/parse_pipeline.c \
									$(PARSER_DIR)/parser.c \
									$(ENV_DIR)/create_env.c \
									$(ENV_DIR)/env_utils.c \
									$(BUILTINS_DIR)/echo.c \
									$(BUILTINS_DIR)/pwd.c \
									$(BUILTINS_DIR)/env.c \
									$(BUILTINS_DIR)/cd.c \
									$(BUILTINS_DIR)/export.c \
									$(BUILTINS_DIR)/unset.c \
									$(BUILTINS_DIR)/exit.c \
									$(BUILTINS_DIR)/builtin_utils.c \
									$(SIGNALS_DIR)/signal_handlers.c \
									$(SIGNALS_DIR)/signal_utils.c \
									$(EXEC_DIR)/exec_redir.c \
									$(EXEC_DIR)/handle_heredoc.c \
									$(EXEC_DIR)/exec_builtin.c \
									$(EXEC_DIR)/exec_cmd.c \
									$(EXEC_DIR)/start_exec.c \
									$(EXEC_DIR)/split_for_path.c \
									$(EXEC_DIR)/heredoc_utils.c \

OBJS							=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT							=	$(LIBFT_DIR)/libft.a

CC								=	cc
CFLAGS							=	-Wall -Wextra -Werror
LDFLAGS							=	-L$(LIBFT_DIR) -lreadline

INCLUDES						=	-I$(INCLUDE_DIR) -I$(LIBFT_DIR)

# Default target
all: $(NAME)

# Link the final executable
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME) $(READLINE)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(FLAGS) $(INCLUDES) -c $< -o $@

# Compile the libft library
$(LIBFT):
	make -C $(LIBFT_DIR)

# Clean object files
clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

# Clean object files and the executable
fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

# Recompile everything
re: fclean all

.PHONY: all clean fclean re

