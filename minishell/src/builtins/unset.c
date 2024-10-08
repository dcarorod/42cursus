/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bproton <bproton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 08:11:14 by proton            #+#    #+#             */
/*   Updated: 2024/09/29 14:05:49 by bproton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_unset(char **env, char **n_env, char **args)
{
	int		i;
	int		j;

	j = -1;
	i = -1;
	while (env[++j])
	{
		if (!should_unset(args, env[j]))
		{
			n_env[++i] = ft_strdup(env[j]);
			if (!n_env)
				exit (1);
		}
	}
	n_env[++i] = NULL;
}

static void	handle_export(char **env, char **n_env, char **args)
{
	int	i;
	int	j;

	i = 0;
	copy_actual_env(env, n_env);
	while (env[i])
		i++;
	j = -1;
	while (args[++j])
	{
		if (!handle_exp_change(n_env, args[j], i))
			continue ;
		n_env[i++] = ft_strdup(args[j]);
		if (!n_env)
			exit (1);
	}
	ft_free_split(args);
	n_env[i] = NULL;
}

size_t	get_array_size(t_hashmap *map)
{
	size_t		i;
	int			size;
	t_env_entry	*tmp;

	i = 0;
	size = 0;
	while (i < map->size)
	{
		tmp = map->buckets[i];
		while (tmp)
		{
			if (tmp->type == ENV_EXP)
				size++;
			tmp = tmp->next;
		}
		i++;
	}
	return (size);
}

char	**resize_env_array(t_hashmap *map, t_global *glob,
		char **args, t_function type)
{
	size_t	new_size;
	char	**n_env;
	char	**n_args;

	if (!args)
		return (NULL);
	n_args = NULL;
	new_size = get_array_size(map);
	n_env = (char **)malloc(sizeof(char *) * (new_size + 1));
	if (!n_env)
		exit (1);
	if (type == UNSET)
		handle_unset(glob->env_arr, n_env, args);
	else if (type == EXP)
	{
		n_args = get_good_args(args);
		handle_export(glob->env_arr, n_env, n_args);
	}
	ft_free_split(glob->env_arr);
	return (n_env);
}

int	ms_unset(char **args, t_hashmap *map, t_global *glob)
{
	int	i;

	if (args[0] && !args[1])
		return (0);
	i = 0;
	while (args[++i])
	{
		if (hashmap_get(map, args[i]))
			hashmap_remove(map, args[i]);
	}
	glob->env_arr = resize_env_array(map, glob, args + 1, UNSET);
	if (!glob->env_arr)
		return (1);
	return (0);
}
