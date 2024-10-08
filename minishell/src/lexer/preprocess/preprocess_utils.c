/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:41:04 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/27 13:47:03 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	check_redir(const char *input, unsigned int *i)
{
	if (LEX_ISREDIR(input[*i]))
	{
		if ((input[*i] == '>' && input[*i + 1] == '>')
			|| (input[*i] == '<' && input[*i + 1] == '<'))
			*i += 2;
		else
			(*i)++;
		while (LEX_ISSPACE(input[*i]))
			(*i)++;
		if (input[*i] == '\0' || LEX_IS_OP(input[*i]))
			return (TRUE);
	}
	return (FALSE);
}

int	has_invalid_redir(const char *input)
{
	int				s_quote;
	int				d_quote;
	unsigned int	i;

	s_quote = FALSE;
	d_quote = FALSE;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (input[i] == '\"' && !s_quote)
			d_quote = !d_quote;
		if (!s_quote && !d_quote)
		{
			if (check_redir(input, &i))
				return (ms_log_val(PT_PRINTF, AST_SYNTAX_ERR_TK, TRUE));
		}
		i++;
	}
	return (FALSE);
}

static int	is_unsupported_symbol(char c)
{
	if (!ft_isprint(c))
		return (TRUE);
	return (c == '&' || c == '(' || c == ')' || c == ';'
		|| c == 92 || c == 96);
}

int	has_unsupported_symbol(const char *input)
{
	int		s_quote;
	int		d_quote;
	size_t	i;

	s_quote = FALSE;
	d_quote = FALSE;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && d_quote == FALSE)
			s_quote = !s_quote;
		else if (input[i] == '\"' && s_quote == FALSE)
			d_quote = !d_quote;
		if (!s_quote && !d_quote)
		{
			if (is_unsupported_symbol(input[i]))
				return (ms_log_val(PT_PRINTF, LEX_UNSUPPORTED_SYMBOL, TRUE));
		}
		i++;
	}
	return (FALSE);
}

int	add_assignment_to_hashmap(char *input, t_global *glob)
{
	char	*key;
	char	*value;
	char	*equal_sign;

	equal_sign = ft_strchr(input, '=');
	if (!equal_sign)
		return (FALSE);
	key = ft_substr(input, 0, equal_sign - input);
	value = ft_strdup(equal_sign + 1);
	if (!key || !value)
	{
		ft_safe_free(2, key, value);
		return (FALSE);
	}
	if (!hashmap_insert(glob->hashmap, key, value, ENV))
	{
		ft_safe_free(2, key, value);
		return (FALSE);
	}
	ft_safe_free(2, key, value);
	return (TRUE);
}
