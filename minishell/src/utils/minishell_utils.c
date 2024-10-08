/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:19:03 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/02 13:45:01 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*update_exit_status(t_global *glob, int exit_status)
{
	char	*value;

	if (!glob)
	{
		ft_putstr("Error: Global structure is NULL\n");
		return (NULL);
	}
	glob->exit_status = exit_status;
	value = ft_itoa(glob->exit_status);
	if (!value)
	{
		ft_putstr("Error: Failed to convert exit status to string\n");
		return (NULL);
	}
	if (!hashmap_insert(glob->hashmap, "?", value, QMARK))
		ft_putstr("Error: Could not update $?\n");
	free(value);
	return (NULL);
}

int	bool_update_status(t_global *glob, int exit_status, int return_value)
{
	update_exit_status(glob, exit_status);
	return (return_value);
}

void	*free_ptr_update_exit(void *ptr_to_free,
	t_global *glob, int exit_status)
{
	if (ptr_to_free)
		free(ptr_to_free);
	return (update_exit_status(glob, exit_status));
}

void	update_exit_set_sigstatus(t_global *glob,
	int exit_status, int signal_status)
{
	update_exit_status(glob, exit_status);
	g_signal_status = signal_status;
}

void	*str_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}
