/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_to_vault.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:53:09 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/24 15:08:27 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Frees the environment list */
void	*vault_free(t_env_vault *vault)
{
	if (vault)
	{
		if (vault->entries)
			free(vault->entries);
		free(vault);
	}
	return (NULL);
}

t_env_vault	*vault_create(size_t num_entries)
{
	t_env_vault	*vault;

	vault = malloc(sizeof(t_env_vault));
	if (!vault)
		return (NULL);
	vault->entries = malloc(sizeof(t_env_entry *) * num_entries);
	if (!vault->entries)
		return (ft_free(vault));
	vault->num_entries = 0;
	vault->env_count = 0;
	vault->exp_count = 0;
	vault->local_count = 0;
	vault->env_exp_count = 0;
	return (vault);
}

/* Adds an entry to the vault and increment the type counters */
static void	add_entry_to_vault(t_env_vault *vault, t_env_entry *entry)
{
	vault->entries[vault->num_entries] = entry;
	vault->num_entries++;
	if (entry->type == ENV)
		vault->env_count++;
	else if (entry->type == EXPORT)
		vault->exp_count++;
	else if (entry->type == LOCAL)
		vault->local_count++;
	else if (entry->type == ENV_EXP)
		vault->env_exp_count++;
	else if (entry->type == QMARK)
		vault->qmark_count++;
}

/* Converts the hashmap to a flat array of not hashed entries (vault) */
t_env_vault	*hashmap_to_vault(t_hashmap *map)
{
	t_env_vault	*vault;
	t_env_entry	*entry;
	size_t		i;
	size_t		num_entries;

	if (!map)
		return (NULL);
	num_entries = map->num_entries;
	vault = vault_create(num_entries + 1);
	if (!vault)
		return (NULL);
	i = 0;
	while (i < map->size)
	{
		entry = map->buckets[i];
		while (entry)
		{
			add_entry_to_vault(vault, entry);
			entry = entry->next;
		}
		i++;
	}
	vault->entries[vault->num_entries] = NULL;
	return (vault);
}
