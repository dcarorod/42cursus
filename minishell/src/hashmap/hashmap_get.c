/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:04:10 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/19 16:18:59 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Returns the value associated to a key */
const char	*hashmap_get(t_hashmap *map, const char *key)
{
	t_env_entry	*entry;
	size_t		index;

	if (!map || !map->buckets || !key)
		return (NULL);
	index = djb2_hash(key, map->size);
	entry = map->buckets[index];
	while (entry)
	{
		if (entry->key && ft_strcmp(entry->key, key) == 0)
			return (entry->value);
		entry = entry->next;
	}
	return (NULL);
}
