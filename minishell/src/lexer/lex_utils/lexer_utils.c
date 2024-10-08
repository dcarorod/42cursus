/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:32:08 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/01 16:58:34 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	*free_lexer_state(t_lexer *lexer)
{
	if (lexer)
	{
		free_tokens(lexer);
		free(lexer);
	}
	return (NULL);
}

char	*ft_strjoin_char(const char *s1, char c)
{
	char	*new_str;
	size_t	len_s1;

	if (!s1)
		return (NULL);
	len_s1 = ft_strlen(s1);
	new_str = (char *)malloc(sizeof(char) * (len_s1 + 2));
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, s1);
	new_str[len_s1] = c;
	new_str[len_s1 + 1] = '\0';
	return (new_str);
}

int	is_valid_key(const char *key)
{
	size_t	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (FALSE);
	i = 1;
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	str_has_space_op(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (LEX_SP_OP(str[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	input_is_assignment(const char *str)
{
	const char	*equal_sign;
	const char	*value;
	size_t		len;

	if (!str || !is_valid_key_part(str))
		return (FALSE);
	equal_sign = strchr(str, '=');
	if (!equal_sign)
		return (FALSE);
	value = equal_sign + 1;
	len = ft_strlen(value);
	if (len == 0 || (value[0] == '\"' && value[len - 1] == '\"')
		|| (value[0] == '\'' && value[len - 1] == '\''))
		return (TRUE);
	if (ft_strchr(value, '\"') || strchr(value, '\''))
		return (FALSE);
	if (str_has_space_op(value))
		return (FALSE);
	return (TRUE);
}

// int	input_is_assignment(const char *str)
// {
// 	const char	*equal_sign;
// 	const char	*value;
// 	size_t		value_len;

// 	if (!str || !is_valid_key_part(str))
// 		return (FALSE);
// 	equal_sign = ft_strchr(str, '=');
// 	if (!equal_sign)
// 		return (FALSE);
// 	value = equal_sign + 1;
// 	value_len = ft_strlen(value);
// 	if (value_len == 0)
// 		return (TRUE);
// 	if (value[0] == '"' && value[value_len - 1] == '"')
// 		return (TRUE);
// 	if (value[0] == '\'' && value[value_len - 1] == '\'')
// 		return (TRUE);
// 	if (ft_strchr(value, '"') || ft_strchr(value, '\''))
// 		return (FALSE);
// 	return (TRUE);
// }
