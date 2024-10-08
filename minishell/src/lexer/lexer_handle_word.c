/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:02:54 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/02 18:11:13 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	process_quotes(t_lexer *lexer, t_global *glob, int *has_quotes)
{
	if (*lexer->current == '\'')
	{
		if (!handle_quote(lexer, SINGLE_QUOTE, NULL))
			return (FALSE);
		*has_quotes = 1;
	}
	else if (*lexer->current == '\"')
	{
		if (!handle_quote(lexer, DOUBLE_QUOTE, glob))
			return (FALSE);
		*has_quotes = 1;
	}
	return (TRUE);
}

static int	process_quote_or_assignment(t_lexer *lexer,
	t_global *glob, int *has_quotes)
{
	while (*lexer->current
		&& !LEX_SP_OP(*lexer->current) && *lexer->current != '$')
	{
		if (str_is_quoted(lexer->start))
		{
			if (!process_quotes(lexer, glob, has_quotes))
				return (FALSE);
		}
		else if (*lexer->current == '=' && is_valid_key_part(lexer->start))
		{
			handle_assignment(lexer, glob);
			return (FALSE);
		}
		else
			lexer->current++;
	}
	return (TRUE);
}

static int	process_env_or_assignment(t_lexer *lexer, t_global *glob)
{
	if (*lexer->current == '$')
	{
		if (ft_strchr(lexer->current, '='))
		{
			handle_assignment(lexer, glob);
			return (TRUE);
		}
		handle_env_var(lexer, glob);
		return (TRUE);
	}
	return (FALSE);
}

void	handle_word(t_lexer *lexer, t_global *glob)
{
	char	*value;
	int		has_quotes;
	char	*processed_value;

	has_quotes = 0;
	if (!process_quote_or_assignment(lexer, glob, &has_quotes))
		return ;
	if (process_env_or_assignment(lexer, glob))
		return ;
	if (!has_quotes && lexer->start != lexer->current)
	{
		value = ft_substr(lexer->start, 0, lexer->current - lexer->start);
		if (value)
		{
			processed_value = remove_quotes_and_join(value);
			add_token(lexer, create_token(WORD, processed_value));
			free(value);
			free(processed_value);
		}
	}
}
