/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:36:13 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/27 13:25:49 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Assign left subtree to the current root (which is the previous command)
	Parse the next command and assign it to the right subtree
	Move root to the new pipe node for further processing
*/
static t_ast	*parser_handle_pipes(t_ast *root, t_lexer *lexer, int *index)
{
	t_ast	*pipe_node;
	t_ast	*cmd_node;

	while (*index < lexer->count)
	{
		if (lexer->tokens[*index]->type == PIPE)
		{
			(*index)++;
			pipe_node = create_ast_node(AST_PIPE);
			if (!pipe_node)
				return (free_multiple_ast(pipe_node, cmd_node, root));
			pipe_node->left = root;
			cmd_node = create_command_node();
			if (!cmd_node)
				return (free_multiple_ast(cmd_node, pipe_node, root));
			if (!parse_pipeline(&cmd_node, lexer, index))
				return (free_multiple_ast(cmd_node, pipe_node, NULL));
			pipe_node->right = cmd_node;
			root = pipe_node;
		}
		else
			break ;
	}
	return (root);
}

/*
	if no pipes, type = AST_COMMAND, then parse_command.
	Parse the first command (or pipeline) and
	Handle any subsequent pipes and connect commands
*/
t_ast	*parse_tokens(t_lexer *lexer)
{
	t_ast	*root;
	int		index;

	if (!lexer || lexer->count == 0)
		return (NULL);
	index = 0;
	root = create_command_node();
	if (!root)
		return (free_ast(root));
	if (!lexer->has_pipe)
	{
		if (!parse_command(root, lexer, &index))
			return (free_ast(root));
		return (root);
	}
	else
	{
		if (!parse_pipeline(&root, lexer, &index))
			return (free_ast(root));
	}
	return (parser_handle_pipes(root, lexer, &index));
}
