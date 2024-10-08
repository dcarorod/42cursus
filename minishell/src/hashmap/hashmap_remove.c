/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:05:31 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/17 12:58:17 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	hashmap_remove(t_hashmap *map, const char *key)
{
	size_t		index;
	t_env_entry	*current;
	t_env_entry	*previous;

	if (!map || !key)
		return (FALSE);
	index = djb2_hash(key, map->size);
	current = map->buckets[index];
	previous = NULL;
	while (current)
	{
		if (current->key && ft_strcmp(current->key, key) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				map->buckets[index] = current->next;
			ft_safe_free(4, current->key,
				current->value, current->prev_value, current);
			return (TRUE);
		}
		previous = current;
		current = current->next;
	}
	return (FALSE);
}
