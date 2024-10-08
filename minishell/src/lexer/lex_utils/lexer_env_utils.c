/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:45:03 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/01 16:07:13 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_valid_start(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '?');
}

int	is_valid_env(char *str)
{
	size_t	i;

	if (!str || (!ft_isalnum(str[1]) && str[1] != '_' && str[1] != '?'))
		return (FALSE);
	if (ft_strcmp(str, "$?") == 0)
		return (TRUE);
	i = 1;
	while (str[i] && !ft_isspace(str[i]))
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '$')
			return (FALSE);
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_invalid_char(str[i + 1]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	is_invalid_char(char c)
{
	return (ft_isdigit(c) || (c >= 33 && c <= 46)
		|| c == 58 || c == 59 || c == 64
		|| (c >= 91 && c <= 96) || c == 123 || c == 125);
}

int	is_valid_var(char *str)
{
	size_t	i;

	if (!str || (!ft_isalnum(str[1]) && str[1] != '_' && str[1] != '?'))
		return (FALSE);
	if (ft_strcmp(str, "$?") == 0)
		return (TRUE);
	i = 1;
	while (str[i] && !ft_isspace(str[i]))
	{
		if (!ft_isalnum(str[i]) && str[i] != '_'
			&& str[i] != '?' && str[i] != '$')
			return (FALSE);
		i++;
	}
	i = 1;
	while (str[i])
	{
		if (str[i] == '$' && is_invalid_char(str[i + 1]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

size_t	count_segments(char **segments)
{
	size_t	segment_count;

	segment_count = 0;
	while (segments[segment_count])
		segment_count++;
	return (segment_count);
}
