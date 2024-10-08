/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:52:32 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/28 23:48:19 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "lexer.h"

# define AST_SYNTAX_ERR_TK "miniHELL: syntax error near unexpected token"
# define AST_MALLOC_ERR_FILE "Failed to allocate memory for file\n"
# define AST_MALLOC_REDIR "Failed to create redir node"

typedef enum e_print_type
{
	PT_PRINTF,
	PT_PERROR
}	t_print_type;

typedef enum e_ast_type
{
	AST_CMD,
	AST_PIPE,
	AST_REDIR
}	t_ast_type;

typedef struct s_command
{
	char	**args;
	int		arg_count;
	int		has_heredoc;
}	t_command;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int				fd;
	struct s_redir	*next;
}	t_redir;

/* Abstract Syntax Tree structure */
typedef struct s_ast
{
	t_ast_type		type;
	t_command		*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
	t_redir			*redir;
}	t_ast;

/* Utils */
t_ast	*create_ast_node(t_ast_type type);
int		is_valid_syntax(t_lexer *lexer);
int		is_redir_tk(t_token_type token_type);

/* cleanup */
void	*free_command(t_command *cmd);
void	*free_redir(t_redir *redir);
void	*free_ast(t_ast *ast);
int		free_ast_bool(t_ast *node, int value);
void	*free_multiple_ast(t_ast *node1, t_ast *node2, t_ast *node3);
void	*pfree_ast(t_ast *ast,
			const char *message, t_print_type print_type);
int		pclean_ast(t_ast *ast, const char *message,
			t_print_type print_type, int value);

/* Parser */
int		parse_redir(t_ast *node, t_lexer *lexer, int *index);
t_ast	*create_command_node(void);
int		parse_command(t_ast *node, t_lexer *lexer, int *index);
int		parse_assignment(t_token *token, t_global *glob);
int		parse_pipeline(t_ast **cmd_node, t_lexer *lexer, int *index);
t_ast	*parse_tokens(t_lexer *lexer);

/* debug */
void	print_ast(t_ast *node);

#endif
