/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:27:29 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/02 01:04:57 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "ms_hashmap.h"

# define LEX_IS_OP(c) (c == '|' || c == '<' || c == '>')
# define LEX_ISREDIR(c) (c == '<' || c == '>')
# define LEX_ISSPACE(c) (c == ' ' || c == '\t')
# define LEX_ISQUOTE(c) (c == '\"' || c == '\'')
# define LEX_SP_OP(c) (LEX_ISSPACE(c) || LEX_IS_OP(c))

# define LEX_ERR_MALLOC "Failed to allocate memory for lexer state"
# define LEX_ERR_TOK_MALLOC  "Failed to allocate memory for tokens array"
# define LEX_UNCLOSED_QUOTE "Error: Unclosed quote detected."
# define LEX_INVALID_REDIR "Error: Invalid redirection."
# define LEX_LOGICAL_OP "Error: Logical operators '&&' and '||' \
are not supported."
# define LEX_OP_START "Error: Misplaced operator at the start of the input"
# define LEX_MISPLACED_OP "Error: Misplaced operators detected."
# define LEX_OP_END "Error: Misplaced operator at the end of the input."
# define LEX_INVALID_INPUT "Invalid input detected. \
Fix the errors and try again."
# define LEX_INV_ASSIGNMENT "Invalid assignment detected"
# define LEX_UNSUPPORTED_SYMBOL "Error: Unsupported symbol detected.\n"

typedef struct s_quote_flag
{
	int	s_quote;
	int	d_quote;
}	t_quote_flag;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	ENV_VAR,
	ASSIGNMENT
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

/*
 * Structure to maintain the state of the lexer
 *
 * tokens: dynamic array of pointers to tokens
 * count: current number of tokens added
 * capacity: current capacity of the tokens array
 * start: pointer to the start of the current token in the input string
 * current: pointer to the current character in the input string
 */
typedef struct s_lexer
{
	t_token	**tokens;
	int		count;
	int		capacity;
	char	*start;
	char	*current;
	int		has_pipe;
	int		has_redir;
	int		has_heredoc;
	int		has_append;
	int		has_env;
	int		has_assignment;
}	t_lexer;

typedef struct s_env
{
	struct s_env	*prev;
	char			*name;
	char			*value;
	t_env_type		type;
	struct s_env	*next;
}					t_env;

typedef struct s_global
{
	char		**env_arr;
	t_env		*env_head;
	t_hashmap	*hashmap;
	t_lexer		*lex_head;
	char		**absolute_path;
	int			exit_status;
}	t_global;

//t_lexer	*ms_lexer(char *input);
t_lexer	*ms_lexer(char *input, t_global *glob);

/* Utils */
int		is_valid_start(char c);
int		is_valid_key(const char *key);
int		is_valid_var(char *str);
int		is_valid_key_part(const char *str);
int		is_invalid_char(char c);
int		is_valid_env(char *str);
size_t	count_segments(char **segments);
int		input_is_assignment(const char *str);
int		str_is_quoted(const char *str);
char	*ft_strjoin_char(const char *s1, char c);
char	*lex_expand_variables(char *value, t_global *glob);
int		add_assignment_to_hashmap(char *input, t_global *glob);
char	*remove_quotes_and_join(const char *str);
char	*extract_dollar_substring(char *str);

char	**segment_string(const char *input);
void	*free_segments(char **segments);

// Utils: lexer
t_token	*create_token(t_token_type type, char *value);
void	add_token(t_lexer *lexer, t_token *token);
void	print_tokens(t_lexer *lexer);
void	free_tokens(t_lexer *lexer);
void	*free_lexer_state(t_lexer *lexer);

// Utils: preprocessing
int		has_invalid_redir(const char *input);
int		has_unsupported_symbol(const char *input);
int		has_invalid_assignment(const char *str);
int		is_valid_input(const char *input);
char	*preprocess_input(char *input, t_global *glob);

/* Lexer handlers */
int		handle_quote(t_lexer *lexer, t_token_type quote_type, t_global *glob);
void	handle_combined(t_lexer *lexer, t_global *glob);
void	handle_special_char(t_lexer *lexer);
void	handle_env_var(t_lexer *lexer, t_global *glob);
void	handle_assignment(t_lexer *lexer, t_global *glob);
void	handle_word(t_lexer *lexer, t_global *glob);

#endif
