/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:32:44 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/27 13:33:49 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Processes the current character in the input string */
void	process_char(t_lexer *lexer, t_global *glob)
{
	if (*(lexer->current) == ' ' || *(lexer->current) == '\t')
	{
		lexer->current++;
		lexer->start = lexer->current;
	}
	else if (*(lexer->current) == '|'
		|| *(lexer->current) == '<' || *(lexer->current) == '>')
		handle_special_char(lexer);
	else
		handle_word(lexer, glob);
}

/* Tokenize the input string */
t_lexer	*ms_lexer(char *input, t_global *glob)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (ms_print_message(LEX_ERR_MALLOC, PT_PRINTF));
	lexer->tokens = malloc(sizeof(t_token *) * 8);
	if (!lexer->tokens)
	{
		free(lexer);
		return (ms_print_message(LEX_ERR_TOK_MALLOC, PT_PRINTF));
	}
	lexer->count = 0;
	lexer->capacity = 8;
	lexer->start = input;
	lexer->current = input;
	lexer->has_pipe = FALSE;
	lexer->has_redir = FALSE;
	lexer->has_append = FALSE;
	lexer->has_heredoc = FALSE;
	lexer->has_env = FALSE;
	lexer->has_assignment = FALSE;
	while (*(lexer->current))
		process_char(lexer, glob);
	return (lexer);
}
