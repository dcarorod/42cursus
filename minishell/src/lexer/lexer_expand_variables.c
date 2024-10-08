/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_variables.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:46:35 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/02 18:10:42 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*extract_exp_value(char *var_name,
	char *expanded_value, t_global *glob)
{
	const char	*env_value;
	char		*temp;

	if (!var_name)
	{
		free(expanded_value);
		exit(EXIT_FAILURE);
	}
	env_value = hashmap_get(glob->hashmap, var_name);
	free(var_name);
	if (env_value)
	{
		temp = ft_strjoin(expanded_value, env_value);
		free(expanded_value);
		expanded_value = temp;
	}
	return (expanded_value);
}

static char	*get_expanded_value(char *value, int *i,
	t_global *glob, char *expanded_value)
{
	int			j;
	char		*var_name;

	j = *i + 1;
	if (value[j] == '?')
	{
		var_name = ft_strdup("?");
		j++;
	}
	else
	{
		while (value[j] && ft_isalnum(value[j]))
			j++;
		var_name = ft_substr(value, *i + 1, j - *i - 1);
	}
	expanded_value = extract_exp_value(var_name, expanded_value, glob);
	*i = j;
	return (expanded_value);
}

static char	*append_char_to_expanded(char *expanded_value, char c)
{
	char	*temp;

	if (!expanded_value)
		return (NULL);
	temp = ft_strjoin_char(expanded_value, c);
	free(expanded_value);
	if (!temp)
		return (NULL);
	return (temp);
}

static char	*handle_status_env(char *exp_val, t_global *glob)
{
	const char	*exit_status_str;
	char		*temp;

	exit_status_str = hashmap_get(glob->hashmap, "?");
	if (exit_status_str)
	{
		temp = ft_strjoin(exp_val, exit_status_str);
		free(exp_val);
		exp_val = temp;
	}
	return (exp_val);
}

char	*lex_expand_variables(char *value, t_global *glob)
{
	char		*exp_val;
	int			i;

	i = 0;
	exp_val = ft_strdup("");
	if (!exp_val)
		exit(EXIT_FAILURE);
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] == '?')
		{
			exp_val = handle_status_env(exp_val, glob);
			i += 2;
		}
		else if (value[i] == '$' && value[i + 1] && ft_isalnum(value[i + 1]))
			exp_val = get_expanded_value(value, &i, glob, exp_val);
		else
		{
			exp_val = append_char_to_expanded(exp_val, value[i]);
			i++;
		}
	}
	return (exp_val);
}
