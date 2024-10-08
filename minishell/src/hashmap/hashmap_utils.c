/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:31:42 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/19 16:21:39 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	djb2_hash(const char *key, size_t map_size)
{
	size_t	hash;
	int		c;

	hash = 5381;
	while (*key)
	{
		c = *key;
		hash = ((hash << 5) + hash) + c;
		key++;
	}
	return (hash % map_size);
}

static void	reinsert_entries(t_hashmap *map,
	t_env_entry **old_buckets, size_t old_size)
{
	size_t		i;
	t_env_entry	*entry;
	t_env_entry	*next;

	i = 0;
	while (i < old_size)
	{
		entry = old_buckets[i];
		while (entry)
		{
			next = entry->next;
			hashmap_insert(map, entry->key, entry->value, entry->type);
			entry = next;
		}
		i++;
	}
}

int	hashmap_resize(t_hashmap *map)
{
	size_t		new_size;
	t_env_entry	**new_buckets;
	t_env_entry	**old_buckets;
	size_t		old_size;

	if (!map)
		return (FALSE);
	old_size = map->size;
	new_size = map->size * 2;
	new_buckets = ft_calloc(new_size, sizeof(t_env_entry *));
	if (!new_buckets)
		return (FALSE);
	old_buckets = map->buckets;
	map->buckets = new_buckets;
	map->size = new_size;
	reinsert_entries(map, old_buckets, old_size);
	free_buckets(old_buckets, old_size);
	return (TRUE);
}
