/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_special_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:22:36 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/02 18:11:20 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_pipe(t_lexer *lexer)
{
	add_token(lexer, create_token(PIPE, "|"));
	lexer->has_pipe = TRUE;
}

static void	handle_in(t_lexer *lexer)
{
	if (*(lexer->current + 1) != '\0' && *(lexer->current + 1) == '<')
	{
		lexer->current++;
		add_token(lexer, create_token(HEREDOC, "<<"));
		lexer->has_heredoc = TRUE;
	}
	else
		add_token(lexer, create_token(REDIR_IN, "<"));
	lexer->has_redir = TRUE;
}

static void	handle_out(t_lexer *lexer)
{
	if (*(lexer->current + 1) != '\0' && *(lexer->current + 1) == '>')
	{
		lexer->current++;
		add_token(lexer, create_token(APPEND, ">>"));
		lexer->has_append = TRUE;
	}
	else
		add_token(lexer, create_token(REDIR_OUT, ">"));
	lexer->has_redir = TRUE;
}

void	handle_special_char(t_lexer *lexer)
{
	if (*lexer->current == '|')
		handle_pipe(lexer);
	else if (*lexer->current == '<')
		handle_in(lexer);
	else if (*lexer->current == '>')
		handle_out(lexer);
	lexer->current++;
	lexer->start = lexer->current;
}
