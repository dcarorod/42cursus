/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:39:03 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/02 18:12:47 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Creates and initializes a new hashmap with the given size */
t_hashmap	*hashmap_create(size_t size)
{
	t_hashmap	*map;

	map = malloc(sizeof(t_hashmap));
	if (!map)
		return (NULL);
	map->size = size;
	map->num_entries = 0;
	map->buckets = ft_calloc(size, sizeof(t_env_entry *));
	if (!map->buckets)
		return (ft_free(map));
	return (map);
}

static int	add_to_hashmap(t_hashmap *map, char *env)
{
	char	*key;
	char	*value;
	char	*equal_sign;

	equal_sign = ft_strchr(env, '=');
	if (!equal_sign)
		return (0);
	key = ft_strndup(env, equal_sign - env);
	value = ft_strdup(equal_sign + 1);
	if (!key || !value || !hashmap_insert(map, key, value, ENV_EXP))
	{
		ft_safe_free(2, key, value);
		return (FALSE);
	}
	ft_safe_free(2, key, value);
	return (TRUE);
}

/*	Initialize hashmap from envp
	Create the hashmap with an initial size
	Iterate through envp to extract keys and values
	Find the position of '=' to split key and value
	Allocate key and value strings
	Insert into the hashmap
	Insert $? to the hashmap
*/
t_hashmap	*hashmap_init(char **envp)
{
	t_hashmap	*map;
	int			i;

	map = hashmap_create(HM_INITIAL_BUCKET_SIZE);
	if (!map)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (!add_to_hashmap(map, envp[i]))
			return (hashmap_free(map));
		i++;
	}
	if (!hashmap_insert(map, "?", "0", QMARK))
	{
		ft_putstr("Could not initialize $?\n");
		return (hashmap_free(map));
	}
	return (map);
}
