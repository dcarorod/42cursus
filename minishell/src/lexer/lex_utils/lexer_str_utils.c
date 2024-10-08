/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_str_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:53:34 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/02 13:04:56 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	str_is_quoted(const char *str)
{
	if (!str || (str[0] == '\0' && str[1] == '\0'))
		return (FALSE);
	return ((str[0] == str[ft_strlen(str) - 1])
		&& (str[0] == '\'' || str[0] == '\"'));
}

int	is_valid_key_part(const char *str)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (FALSE);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	check_quotes(char c, int *in_quotes)
{
	if (*in_quotes == c)
	{
		*in_quotes = 0;
	}
	else if (*in_quotes == 0)
	{
		*in_quotes = c;
	}
	else
		return (0);
	return (1);
}

char	*remove_quotes_and_join(const char *str)
{
	char	*result;
	char	*ptr;
	int		in_quotes;
	size_t	i;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	ptr = result;
	in_quotes = 0;
	i = 0;
	while (str[i])
	{
		if (LEX_ISQUOTE (str[i]) && (i == 0 || str[i - 1] != '\\'))
		{
			if (check_quotes(str[i], &in_quotes))
			{
				i++;
				continue ;
			}
		}
		*ptr++ = str[i++];
	}
	*ptr = '\0';
	return (result);
}

// it works, needs to be refactored for norminette
// char	*remove_quotes_and_join(const char *str)
// {
// 	size_t	len;
// 	char	*result;
// 	char	*ptr;
// 	int		in_quotes;
// 	char	quote_char;
// 	size_t	i;

// 	len = ft_strlen(str);
// 	result = malloc(len + 1);
// 	if (!result)
// 		return (NULL);
// 	ptr = result;
// 	in_quotes = 0;
// 	quote_char = '\0';
// 	i = 0;
// 	while (i < len)
// 	{
// 		if ((str[i] == '"' || str[i] == '\'')
// 			&& (i == 0 || str[i - 1] != '\\'))
// 		{
// 			if (in_quotes && str[i] == quote_char)
// 			{
// 				in_quotes = 0;
// 				quote_char = '\0';
// 			}
// 			else if (!in_quotes)
// 			{
// 				in_quotes = 1;
// 				quote_char = str[i];
// 			}
// 			else
// 				*ptr++ = str[i];
// 		}
// 		else
// 			*ptr++ = str[i];
// 		i++;
// 	}
// 	*ptr = '\0';
// 	return (result);
// }

// int	is_combined_with_dquotes(const char *str)
// {
// 	size_t	i;
// 	size_t	quote_count;

// 	if (str_is_quoted(str))
// 		return (FALSE);
// 	quote_count = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\"')
// 			quote_count++;
// 		i++;
// 	}
// 	if (quote_count >= 2)
// 		return (TRUE);
// 	return (FALSE);
// }
