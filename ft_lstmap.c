/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 21:07:02 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/19 21:30:15 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

lst: The address of a pointer to a node.
f: The address of the function used to iterate on
the list.
del: The address of the function used to delete
the content of a node if needed.

Iterates the list ’lst’ and applies the function
’f’ on the content of each node. Creates a new
list resulting of the successive applications of
the function ’f’. The ’del’ function is used to
delete the content of a node if needed.
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	t_list	*current;
	void	*new_content;

	if (!f || !del)
		return (NULL);
	new_list = NULL;
	new_node = NULL;
	current = lst;
	while (current != NULL)
	{
		new_content = f(current->content);
		if (new_content)
		{
			new_node = ft_lstnew(new_content);
			if (!new_node)
				del(new_content);
		}
		else
			ft_lstadd_back(&new_list, new_node);
		current = current->next;
	}
	return (new_list);
}
