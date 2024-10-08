/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:29:39 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/02 18:11:41 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*free_command(t_command *cmd)
{
	int	i;

	if (cmd)
	{
		if (cmd->args)
		{
			i = 0;
			while (i < cmd->arg_count)
			{
				if (cmd->args[i])
					free(cmd->args[i]);
				i++;
			}
			free(cmd->args);
		}
		free(cmd);
	}
	return (NULL);
}

void	*free_redir(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	current = redir;
	while (current)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		free(current);
		current = next;
	}
	redir = NULL;
	return (NULL);
}

void	*free_ast(t_ast *ast)
{
	if (!ast)
		return (NULL);
	if (ast->cmd)
		free_command(ast->cmd);
	if (ast->redir)
		free_redir(ast->redir);
	if (ast->right)
		free_ast(ast->right);
	if (ast->left)
		free_ast(ast->left);
	free(ast);
	return (NULL);
}

int	free_ast_bool(t_ast *node, int value)
{
	free_ast(node);
	return (value);
}

void	*free_multiple_ast(t_ast *node1, t_ast *node2, t_ast *node3)
{
	if (node1)
		free_ast(node1);
	if (node2)
		free_ast(node2);
	if (node3)
		free_ast(node3);
	return (NULL);
}
