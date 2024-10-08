/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:10:25 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/02 13:05:16 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*get_segment(const char *input, size_t start, size_t end)
{
	size_t	len;
	char	*segment;

	len = end - start;
	segment = (char *)malloc(sizeof(char) * (len + 1));
	if (!segment)
		return (NULL);
	ft_strncpy(segment, &input[start], len);
	segment[len] = '\0';
	return (segment);
}

size_t	handle_quote_segment(const char *input,
	char ***segments, size_t *count, size_t i)
{
	size_t	start;
	char	quote;

	quote = input[i];
	start = i;
	i++;
	while (input[i] != '\0' && !LEX_SP_OP(input[i]))
	{
		if (input[i] == '\\' && quote == '"' && input[i + 1] == '"')
			i += 2;
		else if (input[i] == quote)
		{
			i++;
			break ;
		}
		else
			i++;
	}
	*segments = (char **)str_realloc(*segments, sizeof(char *)
			* (*count + 1), sizeof(char *) * (*count + 2));
	(*segments)[*count] = get_segment(input, start, i);
	if (!(*segments)[*count])
		return ((size_t) - 1);
	(*count)++;
	return (i);
}

size_t	handle_non_quote_segment(const char *input,
	char ***segments, size_t *count, size_t i)
{
	size_t	start;

	start = i;
	while (input[i] && !LEX_ISQUOTE(input[i]) && !LEX_SP_OP(input[i]))
		i++;
	if (i > start)
	{
		*segments = (char **)str_realloc(*segments, sizeof(char *)
				* (*count + 1), sizeof(char *) * (*count + 2));
		(*segments)[*count] = get_segment(input, start, i);
		if (!(*segments)[*count])
			return ((size_t) - 1);
		(*count)++;
	}
	return (i);
}

char	**segment_string(const char *input)
{
	char	**segments;
	size_t	count;
	size_t	i;

	segments = NULL;
	count = 0;
	i = 0;
	while (input[i] != '\0' && !LEX_SP_OP(input[i]))
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = handle_quote_segment(input, &segments, &count, i);
		else
			i = handle_non_quote_segment(input, &segments, &count, i);
		if (i == (size_t) - 1)
			return (NULL);
	}
	segments[count] = NULL;
	return (segments);
}

void	*free_segments(char **segments)
{
	size_t	i;

	if (segments)
	{
		i = 0;
		while (segments[i])
		{
			free(segments[i]);
			i++;
		}
		free(segments);
	}
	return (NULL);
}

// char	**segment_string(const char *input)
// {
// 	char	**segments;
// 	size_t	count;
// 	size_t	i;
// 	size_t	start;
// 	char	quote;

// 	segments = NULL;
// 	count = 0;
// 	start = 0;
// 	quote = '\0';
// 	i = 0;
// 	while (input[i] != '\0' && !LEX_SP_OP(input[i]))
// 	{
// 		if (input[i] == '\'' || input[i] == '\"')
// 		{
// 			quote = input[i];
// 			start = i;
// 			i++;
// 			while (input[i] != '\0' && !LEX_SP_OP(input[i]))
// 			{
// 				if (input[i] == '\\' && quote == '"' && input[i + 1] == '"')
// 					i += 2;
// 				else if (input[i] == quote)
// 				{
// 					i++;
// 					break ;
// 				}
// 				else
// 					i++;
// 			}
// 			segments = (char **)str_realloc(segments, sizeof(char *)
// 					* (count + 1), sizeof(char *) * (count + 2));
// 			segments[count] = get_segment(input, start, i);
// 			if (!segments[count])
// 				return (NULL);
// 			count++;
// 		}
// 		else
// 		{
// 			start = i;
// 			while (input[i] && !LEX_ISQUOTE(input[i]) && !LEX_SP_OP(input[i]))
// 				i++;
// 			if (i > start)
// 			{
// 				segments = (char **)str_realloc(segments, sizeof(char *)
// 						* (count + 1), sizeof(char *) * (count + 2));
// 				segments[count] = get_segment(input, start, i);
// 				if (!segments[count])
// 					return (NULL);
// 				count++;
// 			}
// 		}
// 	}
// 	segments[count] = NULL;
// 	return (segments);
// }

// void	*free_two_segments(char **segment1, char **segment2)
// {
// 	if (segment1)
// 		free_segments(segment1);
// 	if (segment2)
// 		free_segments(segment2);
// 	return (NULL);
// }

/*
char	**segment_string(const char *input)
{
	char	**segments;
	size_t	count;
	size_t	i;
	size_t	start;
	char	quote;

	segments = NULL;
	count = 0;
	start = 0;
	quote = '\0';
	i = 0;
	while (input[i] != '\0' && !LEX_SP_OP(input[i]))
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i];
			start = i;
			i++;
			while (input[i] != '\0' && !LEX_SP_OP(input[i]))
			{
				if (input[i] == '\\' && quote == '"' && input[i + 1] == '"')
					i += 2;
				else if (input[i] == quote)
				{
					i++;
					break ;
				}
				else
					i++;
			}
			segments = (char **)str_realloc(segments, sizeof(char *)
					* (count + 1), sizeof(char *) * (count + 2));
			segments[count] = get_segment(input, start, i);
			if (!segments[count])
				return (NULL);
			count++;
		}
		else
		{
			start = i;
			while (input[i] && !LEX_ISQUOTE(input[i]) && !LEX_SP_OP(input[i]))
				i++;
			if (i > start)
			{
				segments = (char **)str_realloc(segments, sizeof(char *)
						* (count + 1), sizeof(char *) * (count + 2));
				segments[count] = get_segment(input, start, i);
				if (!segments[count])
					return (NULL);
				count++;
			}
		}
	}
	segments[count] = NULL;
	return (segments);
}
*/
