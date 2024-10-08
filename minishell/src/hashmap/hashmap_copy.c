/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:41:07 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/23 14:44:09 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Iterate through all the buckets of the old hashmap
// Insert each key-value pair into the new hashmap
t_hashmap	*hashmap_copy(t_hashmap *map)
{
	t_hashmap	*new_map;
	size_t		i;
	t_env_entry	*entry;

	if (!map)
		return (NULL);
	new_map = hashmap_create(map->size);
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < map->size)
	{
		entry = map->buckets[i];
		while (entry)
		{
			if (!hashmap_insert(new_map, entry->key, entry->value, entry->type))
				return (hashmap_free(new_map));
			entry = entry->next;
		}
		i++;
	}
	return (new_map);
}
