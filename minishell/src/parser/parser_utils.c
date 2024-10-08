/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:55:07 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/02 18:11:47 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*create_ast_node(t_ast_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->cmd = NULL;
	node->left = NULL;
	node->right = NULL;
	node->redir = NULL;
	return (node);
}

// Initial capacity for 8 arguments + 1 for NULL termination
t_ast	*create_command_node(void)
{
	t_ast	*node;
	size_t	i;

	node = create_ast_node(AST_CMD);
	if (!node)
		return (NULL);
	node->cmd = malloc(sizeof(t_command));
	if (!node->cmd)
		return (free_ast(node));
	node->cmd->args = malloc(sizeof(char *) * (8 + 1));
	if (!node->cmd->args)
		return (free_ast(node));
	node->cmd->arg_count = 0;
	node->cmd->has_heredoc = 0;
	i = 0;
	while (i < 9)
	{
		node->cmd->args[i] = NULL;
		i++;
	}
	return (node);
}

int	is_valid_syntax(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (i < lexer->count)
	{
		if (lexer->tokens[i]->type == PIPE)
		{
			if (i == 0 || i == lexer->count - 1
				|| lexer->tokens[i + 1]->type == PIPE)
				return (ms_log_val(PT_PRINTF, AST_SYNTAX_ERR_TK, FALSE));
		}
		i++;
	}
	return (TRUE);
}

int	is_redir_tk(t_token_type token_type)
{
	return (token_type == REDIR_IN || token_type == REDIR_OUT
		|| token_type == APPEND || token_type == HEREDOC);
}
