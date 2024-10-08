/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:36:06 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/27 13:47:47 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_argument(t_command *cmd, char *arg)
{
	char	**new_args;

	if (cmd->arg_count % 8 == 0 && cmd->arg_count != 0)
	{
		new_args = ft_realloc(cmd->args,
				sizeof(char *) * (cmd->arg_count + 8 + 1));
		if (!new_args)
		{
			perror("realloc memory for command args failed");
			free_command(cmd);
			return (FALSE);
		}
		cmd->args = new_args;
	}
	cmd->args[cmd->arg_count] = ft_strdup(arg);
	if (!cmd->args[cmd->arg_count])
	{
		perror("ft_strdup failed");
		free_command(cmd);
		return (FALSE);
	}
	cmd->arg_count++;
	cmd->args[cmd->arg_count] = NULL;
	return (TRUE);
}

static int	is_special_token(t_token *token)
{
	return (token->type == PIPE
		|| token->type == APPEND || token->type == HEREDOC
		|| token->type == REDIR_IN || token->type == REDIR_OUT);
}

static int	handle_special_token(t_ast *node, t_lexer *lexer, int *index)
{
	if (is_redir_tk(lexer->tokens[*index]->type))
	{
		if (!parse_redir(node, lexer, index))
			return (FALSE);
	}
	else if (lexer->tokens[*index]->type == PIPE)
		return (FALSE);
	return (TRUE);
}

int	parse_command(t_ast *node, t_lexer *lexer, int *index)
{
	t_command	*cmd;

	cmd = node->cmd;
	while (*index < lexer->count)
	{
		if (is_special_token(lexer->tokens[*index]))
		{
			if (!handle_special_token(node, lexer, index))
				break ;
		}
		else
		{
			if (!add_argument(cmd, lexer->tokens[*index]->value))
				return (FALSE);
			(*index)++;
		}
	}
	return (TRUE);
}
