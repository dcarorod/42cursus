/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:32:32 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/29 18:45:24 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Make copies of the new value before freeing anything
	In case of allocation failure, clean up and return
	Free the old previous value
	Update prev_value and value
	Update the type
*/
static int	update_entry(t_env_entry *entry,
	const char *new_value, t_env_type type)
{
	char	*new_prev_value;
	char	*new_value_copy;

	if (!entry->value || !entry->prev_value)
		return (FALSE);
	new_prev_value = ft_strdup(entry->value);
	new_value_copy = ft_strdup(new_value);
	if (!new_prev_value || !new_value_copy)
	{
		ft_safe_free(2, new_prev_value, new_value_copy);
		return (FALSE);
	}
	ft_free(entry->prev_value);
	entry->prev_value = new_prev_value;
	ft_free(entry->value);
	entry->value = new_value_copy;
	entry->type = type;
	return (TRUE);
}

int	hashmap_update(t_hashmap *map,
	const char *key, const char *new_value, t_env_type type)
{
	size_t		index;
	t_env_entry	*entry;

	if (!map || !key || !new_value)
		return (FALSE);
	index = djb2_hash(key, map->size);
	entry = map->buckets[index];
	while (entry)
	{
		if (ft_strcmp(entry->key, key) == 0)
			return (update_entry(entry, new_value, type));
		entry = entry->next;
	}
	return (FALSE);
}

static t_env_entry	*insert_new_entry(const char *key, const char *value,
	t_env_type type)
{
	t_env_entry	*entry;

	if (!key || !value)
		return (NULL);
	entry = malloc(sizeof(t_env_entry));
	if (!entry)
		return (NULL);
	entry->key = ft_strdup(key);
	entry->value = ft_strdup(value);
	entry->prev_value = ft_strdup(value);
	if (!entry->key || !entry->value || !entry->prev_value)
		return (free_env_entry(entry));
	entry->type = type;
	entry->next = NULL;
	return (entry);
}

/*	Inserts a new entry into the hashmap.
	If the key already exists, update it.
	Otherwise, insert a new entry. */
int	hashmap_insert(t_hashmap *map,
	const char *key, const char *value, t_env_type type)
{
	size_t		index;
	t_env_entry	*new_entry;
	t_env_entry	*entry;

	if (map->num_entries >= (map->size * HM_LOAD_FACTOR_THRESHOLD))
	{
		if (!hashmap_resize(map))
			return (FALSE);
	}
	index = djb2_hash(key, map->size);
	entry = map->buckets[index];
	while (entry)
	{
		if (ft_strcmp(entry->key, key) == 0)
			return (hashmap_update(map, key, value, type));
		entry = entry->next;
	}
	new_entry = insert_new_entry(key, value, type);
	if (!new_entry)
		return (FALSE);
	new_entry->next = map->buckets[index];
	map->buckets[index] = new_entry;
	map->num_entries++;
	return (TRUE);
}
