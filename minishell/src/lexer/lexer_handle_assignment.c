/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_assignment.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:50:41 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/02 18:10:50 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	add_word_or_assignment_token(t_lexer *lexer,
	char *key_part, char *final_value)
{
	if (ft_strchr(key_part, '$'))
		add_token(lexer, create_token(WORD, final_value));
	else
	{
		add_token(lexer, create_token(ASSIGNMENT, final_value));
		lexer->has_assignment = TRUE;
	}
}

static char	*extract_value_with_quotes(t_lexer *lexer, t_global *glob)
{
	char	quote;
	char	*value_part;
	char	*expanded_value;

	quote = *lexer->current;
	lexer->current++;
	lexer->start = lexer->current;
	while (*lexer->current && *lexer->current != quote)
		lexer->current++;
	value_part = ft_substr(lexer->start, 0, lexer->current - lexer->start);
	lexer->current++;
	if (quote == '\"')
	{
		expanded_value = lex_expand_variables(value_part, glob);
		free(value_part);
	}
	else
		expanded_value = value_part;
	return (expanded_value);
}

static char	*extract_value_without_quotes(t_lexer *lexer, t_global *glob)
{
	char	*value_part;
	char	*expanded_value;

	lexer->start = lexer->current;
	while (*lexer->current && !LEX_SP_OP(*lexer->current))
		lexer->current++;
	value_part = ft_substr(lexer->start, 0, lexer->current - lexer->start);
	expanded_value = lex_expand_variables(value_part, glob);
	free(value_part);
	return (expanded_value);
}

static char	*get_expanded_key_value(char *expanded_key, char *expanded_value)
{
	char	*temp;
	char	*final_value;

	temp = ft_strjoin(expanded_key, "=");
	if (!temp)
		exit(EXIT_FAILURE);
	final_value = ft_strjoin(temp, expanded_value);
	free(temp);
	if (!final_value)
		exit(EXIT_FAILURE);
	return (final_value);
}

void	handle_assignment(t_lexer *lexer, t_global *glob)
{
	char	*key_part;
	char	*expanded_value;
	char	*expanded_key;
	char	*final_value;
	char	*start;

	start = lexer->start;
	while (*start && *start != '=')
		start++;
	key_part = ft_substr(lexer->start, 0, start - lexer->start);
	if (!key_part)
		exit(EXIT_FAILURE);
	expanded_key = lex_expand_variables(key_part, glob);
	lexer->current = start + 1;
	if (*lexer->current == '\'' || *lexer->current == '\"')
		expanded_value = extract_value_with_quotes(lexer, glob);
	else
		expanded_value = extract_value_without_quotes(lexer, glob);
	final_value = get_expanded_key_value(expanded_key, expanded_value);
	add_word_or_assignment_token(lexer, key_part, final_value);
	ft_safe_free(4, key_part, expanded_key, expanded_value, final_value);
}
