/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 21:09:23 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/02 18:11:06 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_quote_content(t_lexer *lexer,
	t_token_type quote_type, char *start, t_global *glob)
{
	char	*value;
	char	*expanded_value;

	if (lexer->current == start)
		value = ft_strdup("");
	else
		value = ft_strndup(start, lexer->current - start);
	if (!value)
		return (FALSE);
	lexer->current++;
	if (quote_type == DOUBLE_QUOTE)
		expanded_value = lex_expand_variables(value, glob);
	else
		expanded_value = ft_strdup(value);
	free(value);
	if (!expanded_value)
		return (FALSE);
	add_token(lexer, create_token(quote_type, expanded_value));
	free(expanded_value);
	return (TRUE);
}

int	handle_quote(t_lexer *lexer, t_token_type quote_type, t_global *glob)
{
	char	*start;
	char	current_char;

	start = ++(lexer->current);
	while (*(lexer->current))
	{
		current_char = *lexer->current;
		if ((quote_type == SINGLE_QUOTE && current_char == '\'')
			|| (quote_type == DOUBLE_QUOTE && current_char == '\"'))
			break ;
		lexer->current++;
	}
	if (*(lexer->current))
		return (handle_quote_content(lexer, quote_type, start, glob));
	else
	{
		printf("Unclosed quote detected. Please close the quote.\n");
		return (FALSE);
	}
}
