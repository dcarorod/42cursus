/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vault_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:01:55 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/24 14:53:55 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	compare_keys(t_env_entry *entry_a, t_env_entry *entry_b)
{
	return (ft_strcmp(entry_a->key, entry_b->key));
}

/* Swap two entries in the vault */
static void	swap_entries(t_env_entry **a, t_env_entry **b)
{
	t_env_entry	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	vault_sort(t_env_vault *vault)
{
	size_t	i;
	size_t	j;
	int		swapped;

	if (!vault || vault->num_entries < 2)
		return ;
	i = 0;
	while (i < vault->num_entries - 1)
	{
		swapped = 0;
		j = 0;
		while (j < vault->num_entries - i - 1)
		{
			if (compare_keys(vault->entries[j], vault->entries[j + 1]) > 0)
			{
				swap_entries(&vault->entries[j], &vault->entries[j + 1]);
				swapped = 1;
			}
			j++;
		}
		if (!swapped)
			break ;
		i++;
	}
}
