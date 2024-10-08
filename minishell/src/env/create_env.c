/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:12:23 by bproton           #+#    #+#             */
/*   Updated: 2024/10/02 11:22:36 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*each_envp_line(char *env_line, int name)
{
	int		i;
	char	*new_line;

	i = 0;
	if (name == 1)
		new_line = ft_strdup(env_line);
	else
	{
		while (env_line[i] != '=')
			i++;
		i++;
		new_line = ft_strdup(env_line + i);
	}
	if (!new_line)
	{
		perror("error getting the new line");
		return (NULL);
	}
	return (new_line);
}

char	**get_envp_array(char **envp)
{
	char	**new_env;
	int		i;
	int		j;

	j = 0;
	while (envp[j])
		j++;
	new_env = (char **)malloc(sizeof(char *) * (j + 1));
	if (!new_env)
		exit (1);
	i = -1;
	while (++i < j)
	{
		new_env[i] = each_envp_line(envp[i], 1);
		if (!new_env[i])
		{
			ft_free_split(new_env);
			exit (1);
		}
	}
	new_env[i] = NULL;
	return (new_env);
}

static char	**get_null_envp(void)
{
	char	**n_env;
	char	dir[1024];
	char	*str;

	str = getcwd(dir, sizeof(dir) - 1);
	n_env = (char **)malloc(sizeof(char *) * 4);
	if (!n_env)
		return (NULL);
	n_env[0] = ft_strjoin("PWD=", str);
	if (!n_env[0])
		return (NULL);
	n_env[1] = ft_strdup("SHLVL=1");
	if (!n_env[1])
		return (NULL);
	n_env[2] = ft_strdup("_=/usr/bin/env");
	if (!n_env[2])
		return (NULL);
	return (n_env);
}

int	create_env_list(t_global *global, char **envp)
{
	if (!envp[0])
	{
		global->env_arr = get_null_envp();
		global->absolute_path = get_null_envp();
		global->hashmap = hashmap_init(get_null_envp());
		if (!global->env_arr)
		{
			ft_free_split(global->env_arr);
			exit (1);
		}
		else if (!global->absolute_path)
		{
			ft_free_split(global->absolute_path);
			exit (1);
		}
	}
	else
	{
		global->env_arr = get_envp_array(envp);
		global->absolute_path = get_envp_array(envp);
		global->hashmap = hashmap_init(envp);
		if (!global->hashmap)
			return (-1);
	}
	return (0);
}
