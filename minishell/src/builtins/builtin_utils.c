/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proton <proton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:20:26 by proton            #+#    #+#             */
/*   Updated: 2024/09/27 18:38:57 by proton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	copy_actual_env(char **env, char **n_env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		n_env[i] = ft_strdup(env[i]);
		if (!n_env[i])
		{
			ft_free_split(n_env);
			exit (1);
		}
	}
}

int	handle_exp_change(char **n_env, char *arg, int len)
{
	int		i;
	char	key[50];
	char	key2[50];

	i = -1;
	while (++i < len)
	{
		if (ft_strcmp(extract_name(n_env[i], key),
				extract_name(arg, key2)) == 0)
		{
			free(n_env[i]);
			n_env[i] = ft_strdup(arg);
			if (!n_env[i])
				exit(1);
			return (0);
		}
	}
	return (1);
}

static int	add_arg(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '=')
			return (1);
	}
	return (0);
}

char	**get_good_args(char **args)
{
	int		i;
	int		j;
	char	**new_args;

	i = -1;
	j = 0;
	while (args[++i])
	{
		if (add_arg(args[i]))
			j++;
	}
	new_args = (char **)malloc(sizeof(char *) * (j + 1));
	if (!new_args)
		exit (1);
	i = -1;
	j = -1;
	while (args[++i])
	{
		if (add_arg(args[i]))
			new_args[++j] = ft_strdup(args[i]);
	}
	new_args[++j] = NULL;
	return (new_args);
}
