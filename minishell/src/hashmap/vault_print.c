/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vault_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proton <proton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:39:56 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/24 17:38:16 by proton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	vault_print_export(t_env_vault *sorted_vault)
{
	size_t		i;
	t_env_entry	*entry;

	i = 0;
	while (i < sorted_vault->num_entries)
	{
		entry = sorted_vault->entries[i];
		if (entry->type == ENV_EXP)
		{
			ft_putstr("declare -x ");
			ft_putstr(entry->key);
			ft_putstr("=\"");
			ft_putstr(entry->value);
			ft_putstr("\"\n");
		}
		else if (entry->type == EXPORT)
		{
			ft_putstr("declare -x ");
			ft_putstr(entry->key);
			ft_putchar('\n');
		}
		i++;
	}
}

/* Prints key=value pair of provided type*/
void	vault_print_by_type(t_env_vault *sorted, t_env_type type)
{
	size_t		i;
	t_env_entry	*entry;

	i = 0;
	while (i < sorted->num_entries)
	{
		entry = sorted->entries[i];
		if (type == entry->type)
		{
			ft_putstr(entry->key);
			ft_putchar('=');
			ft_putstr(entry->value);
			ft_putchar('\n');
		}
		i++;
	}
}
