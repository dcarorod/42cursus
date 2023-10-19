/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:46:40 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/19 20:50:25 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
void	ft_lstiter(t_list *lst, void (*f)(void *));

lst: The address of a pointer to a node.
f: The address of the function used to iterate on
the list.
Iterates the list ’lst’ and applies the function
’f’ on the content of each node.
*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;

	current = lst;
	while (current != NULL)
	{
		if (f != NULL)
			f(current->content);
		current = current->next;
	}
}
