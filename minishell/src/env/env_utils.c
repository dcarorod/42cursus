/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bproton <bproton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:41:13 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/29 14:06:36 by bproton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	should_unset(char **args, char *env_var)
{
	int		i;
	char	key[50];

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(extract_name(env_var, key), args[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*extract_name(char *env, char *key)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (env[i] == '=')
			break ;
		key[i] = env[i];
	}
	key[i] = '\0';
	return (key);
}

int	handle_cd_change(t_global *glob, char **args)
{
	int		i;
	int		j;
	char	key[50];
	char	key2[50];

	i = -1;
	while (glob->env_arr[++i])
	{
		j = -1;
		while (args[++j])
		{
			if (ft_strcmp(extract_name(glob->env_arr[i], key),
					extract_name(args[j], key2)) == 0)
			{
				free(glob->env_arr[i]);
				glob->env_arr[i] = ft_strdup(args[j]);
				if (!glob->env_arr[i])
					exit(1);
			}
		}
	}
	return (1);
}

char	**add_to_array(char **env, char *str, int len)
{
	int		i;
	char	**n_env;

	i = 0;
	n_env = (char **)malloc(sizeof(char *) * (len + 5));
	if (!n_env)
		exit (1);
	while (env[i])
	{
		n_env[i] = ft_strdup(env[i]);
		if (!n_env[i])
			exit (1);
		i++;
	}
	n_env[i++] = ft_strdup(str);
	if (!n_env[i - 1])
		exit (1);
	n_env[i] = NULL;
	ft_free_split(env);
	return (n_env);
}

int	search_to_add(t_global *glob, char *dir, int len)
{
	int		i;
	int		arr_found;
	char	*array;

	i = -1;
	arr_found = 0;
	if (len == 5)
		array = ft_strjoin("PWD=", dir);
	else
		array = ft_strjoin("OLDPWD=", dir);
	if (!array)
		exit (1);
	while (glob->env_arr[++i])
	{
		if (ft_strcmp(glob->env_arr[i], array) == 0)
			arr_found = 1;
	}
	if (arr_found == 0)
		glob->env_arr = add_to_array(glob->env_arr, array, i);
	free (array);
	return (0);
}
