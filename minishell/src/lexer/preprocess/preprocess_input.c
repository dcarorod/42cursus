/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:25:10 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/01 16:45:56 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	has_unclosed_quotes(const char *input)
{
	int	s_quote;
	int	d_quote;

	s_quote = FALSE;
	d_quote = FALSE;
	while (*input)
	{
		if (*input == '\'' && d_quote == FALSE)
			s_quote = !s_quote;
		else if (*input == '\"' && s_quote == FALSE)
			d_quote = !d_quote;
		input++;
	}
	if (s_quote || d_quote)
	{
		printf("%s\n", LEX_UNCLOSED_QUOTE);
		return (TRUE);
	}
	return (FALSE);
}

static int	has_logical_op(const char *input)
{
	int				in_sq;
	int				in_dq;
	const char		*ptr;

	in_sq = FALSE;
	in_dq = FALSE;
	ptr = input;
	while (*ptr)
	{
		if (*ptr == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (*ptr == '\"' && !in_sq)
			in_dq = !in_dq;
		if (!in_sq && !in_dq)
		{
			if ((*ptr == '|' && *(ptr + 1) == '|')
				|| (*ptr == '&' && *(ptr + 1) == '&'))
				return (ms_log_val(PT_PRINTF, LEX_LOGICAL_OP, TRUE));
		}
		ptr++;
	}
	return (FALSE);
}

static int	has_misplaced_op(const char *input)
{
	size_t	len;

	len = ft_strlen(input);
	if (input[0] == '|' || LEX_IS_OP(input[len - 1])
		|| (LEX_IS_OP(input[len - 1]) && LEX_IS_OP(input[len - 2])))
		return (ms_log_val(PT_PRINTF, AST_SYNTAX_ERR_TK, TRUE));
	return (FALSE);
}

int	is_valid_input(const char *input)
{
	if (!input)
		return (FALSE);
	if (has_unclosed_quotes(input) || has_logical_op(input)
		|| has_misplaced_op(input) || has_invalid_redir(input)
		|| has_unsupported_symbol(input))
		return (FALSE);
	return (TRUE);
}

char	*preprocess_input(char *input, t_global *glob)
{
	char	*trimmed;

	if (!input)
		return (NULL);
	trimmed = ft_strtrim(input, " \t");
	if (!trimmed)
		return (NULL);
	if (ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		return (ft_strdup(""));
	}
	if (input_is_assignment(trimmed))
	{
		if (!add_assignment_to_hashmap(trimmed, glob))
			return (ft_free(trimmed));
		free(trimmed);
		return (ft_strdup(""));
	}
	if (!is_valid_input(trimmed))
	{
		update_exit_status(glob, 2);
		return (ft_free(trimmed));
	}
	return (trimmed);
}

// char	*preprocess_input(char *input, t_global *glob)
// {
// 	char	*trimmed;

// 	if (!input)
// 		return (NULL);
// 	trimmed = ft_strtrim(input, " \t");
// 	if (!trimmed)
// 		return (NULL);
// 	if (ft_strlen(trimmed) == 0)
// 	{
// 		free(trimmed);
// 		return (ft_strdup(""));
// 	}
// 	if (input_is_assignment(trimmed))
// 	{
// 		if (!add_assignment_to_hashmap(trimmed, glob))
// 			return (ft_free(trimmed));
// 		free(trimmed);
// 		trimmed = ft_strdup("");
// 		if (!trimmed)
// 			return (NULL);
// 		return (trimmed);
// 	}
// 	if (!is_valid_input(trimmed))
// 		return (free_ptr_update_exit(trimmed, glob, 2));
// 	return (trimmed);
// }

// char	*preprocess_input(char *input, t_global *glob)
// {
// 	char	*trimmed;

// 	if (!input)
// 		return (NULL);
// 	trimmed = ft_strtrim(input, " \t");
// 	if (!trimmed)
// 		return (NULL);
// 	if (ft_strlen(trimmed) == 0)
// 	{
// 		free(trimmed);
// 		return (ft_strdup(""));
// 	}
// 	if (input_is_assignment(trimmed))
// 	{
// 		if (!add_assignment_to_hashmap(trimmed, glob))
// 			return (ft_free(trimmed));
// 		free(trimmed);
// 		trimmed = ft_strdup("");
// 		if (!trimmed)
// 			return (NULL);
// 		return (trimmed);
// 	}
// 	if (!is_valid_input(trimmed))
// 	{
// 		update_exit_status(glob, 2);
// 		return (ft_free(trimmed));
// 	}
// 	return (trimmed);
// }

/*int	is_valid_input(const char *input, t_global *glob)
{
	//char	*exit_status;

	if (!input)
		return (FALSE);
	if (has_unclosed_quotes(input) || has_logical_op(input)
		|| has_misplaced_op(input) || has_invalid_redir(input)
		|| has_unsupported_symbol(input, glob))
		{
			// glob->exit_status = 2;
			// exit_status = ft_itoa(glob->exit_status);
			// hashmap_update(glob->hashmap, "?", exit_status, QMARK);
			return (FALSE);
		}
	return (TRUE);
}*/
