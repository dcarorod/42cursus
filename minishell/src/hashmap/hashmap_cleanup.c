/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:09:55 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/02 18:12:38 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*free_env_entry(t_env_entry *entry)
{
	if (entry)
	{
		if (entry->key)
		{
			free(entry->key);
			entry->key = NULL;
		}
		if (entry->value)
		{
			free(entry->value);
			entry->value = NULL;
		}
		if (entry->prev_value)
		{
			free(entry->prev_value);
			entry->prev_value = NULL;
		}
		free(entry);
		entry = NULL;
	}
	return (NULL);
}

void	*free_buckets(t_env_entry **buckets, size_t size)
{
	size_t		i;
	t_env_entry	*current;
	t_env_entry	*tmp;

	i = 0;
	while (i < size)
	{
		current = buckets[i];
		while (current)
		{
			tmp = current->next;
			free_env_entry(current);
			current = tmp;
		}
		i++;
	}
	free(buckets);
	buckets = NULL;
	return (NULL);
}

void	*hashmap_free(t_hashmap *map)
{
	free_buckets(map->buckets, map->size);
	free(map);
	return (NULL);
}
