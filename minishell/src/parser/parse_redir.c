/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:08:35 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/22 18:34:53 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	attach_redir_node(t_ast *node, t_redir *redir_node)
{
	t_redir	*last_redir;

	if (node->redir)
	{
		last_redir = node->redir;
		while (last_redir->next)
			last_redir = last_redir->next;
		last_redir->next = redir_node;
	}
	else
		node->redir = redir_node;
}

int	parse_redir(t_ast *node, t_lexer *lexer, int *index)
{
	t_redir	*redir_node;

	if (*index >= lexer->count || !is_redir_tk(lexer->tokens[*index]->type))
		return (FALSE);
	if (*index + 1 >= lexer->count || lexer->tokens[*index + 1]->type != WORD)
		return (ms_log_val(PT_PRINTF, AST_SYNTAX_ERR_TK, FALSE));
	redir_node = malloc(sizeof(t_redir));
	if (!redir_node)
	{
		free(redir_node);
		return (FALSE);
	}
	redir_node->type = lexer->tokens[*index]->type;
	redir_node->file = ft_strdup(lexer->tokens[*index + 1]->value);
	if (!redir_node->file)
	{
		free_redir(redir_node);
		return (FALSE);
	}
	redir_node->fd = -1;
	redir_node->next = NULL;
	attach_redir_node(node, redir_node);
	(*index) += 2;
	return (TRUE);
}
