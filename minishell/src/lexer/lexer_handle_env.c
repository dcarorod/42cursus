/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:29:44 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/02 18:10:58 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*expand_segment(char *segment, t_global *glob)
{
	char	*content;
	char	*expanded_segment;

	if (!segment)
		return (NULL);
	if (segment[0] == '\'' && segment[ft_strlen(segment) - 1] == '\'')
	{
		expanded_segment = ft_substr(segment, 1, ft_strlen(segment) - 2);
		if (!expanded_segment)
			return (NULL);
	}
	else if (segment[0] == '\"' && segment[ft_strlen(segment) - 1] == '\"')
	{
		content = ft_substr(segment, 1, ft_strlen(segment) - 2);
		if (!content)
			return (NULL);
		expanded_segment = lex_expand_variables(content, glob);
		free(content);
	}
	else
		expanded_segment = lex_expand_variables(segment, glob);
	if (expanded_segment)
		return (expanded_segment);
	return (NULL);
}

// expand segments and free original segments
static char	**expand_segments(char **segments, t_global *glob)
{
	int		i;
	char	**expanded_segments;
	int		segment_count;

	i = 0;
	segment_count = count_segments(segments);
	expanded_segments = malloc((segment_count + 1) * sizeof(char *));
	if (!expanded_segments)
		exit(EXIT_FAILURE);
	while (i < segment_count)
	{
		expanded_segments[i] = expand_segment(segments[i], glob);
		if (!expanded_segments[i])
		{
			while (i > 0)
				free(expanded_segments[--i]);
			free(expanded_segments);
			return (NULL);
		}
		i++;
	}
	expanded_segments[segment_count] = NULL;
	free_segments(segments);
	return (expanded_segments);
}

static char	*concat_segments(char **segments)
{
	size_t	total_length;
	size_t	i;
	size_t	offset;
	char	*combined;

	total_length = 0;
	i = 0;
	while (segments[i])
	{
		total_length += ft_strlen(segments[i]);
		i++;
	}
	combined = malloc(sizeof(char) * (total_length + 1));
	if (!combined)
		exit(EXIT_FAILURE);
	offset = 0;
	i = 0;
	while (segments[i])
	{
		ft_strcpy(combined + offset, segments[i]);
		offset += ft_strlen(segments[i]);
		i++;
	}
	combined[total_length] = '\0';
	return (combined);
}

static void	add_token_and_free(t_lexer *lexer,
	char **expanded_segments, int var_only)
{
	char	*value;

	value = concat_segments(expanded_segments);
	if (!value)
		exit(EXIT_FAILURE);
	free_segments(expanded_segments);
	if (var_only)
	{
		add_token(lexer, create_token(ENV_VAR, value));
		lexer->has_env = TRUE;
	}
	else
		add_token(lexer, create_token(WORD, value));
	free(value);
}

void	handle_env_var(t_lexer *lexer, t_global *glob)
{
	char	*start;
	char	**segments;
	char	**expanded_segments;
	int		var_only;

	var_only = 0;
	if (*lexer->start == '$')
		start = lexer->current;
	else
		start = lexer->start;
	segments = segment_string(start);
	if (!segments)
		exit(EXIT_FAILURE);
	if (count_segments(segments) == 1 && is_valid_env(segments[0]))
		var_only = 1;
	expanded_segments = expand_segments(segments, glob);
	if (!expanded_segments)
		exit(EXIT_FAILURE);
	add_token_and_free(lexer, expanded_segments, var_only);
	while (*lexer->current && !LEX_SP_OP(*lexer->current))
		lexer->current++;
}
