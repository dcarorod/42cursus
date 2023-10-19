/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:09:10 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/10/19 18:14:34 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Counts the number of nodes in a list. */

int	ft_lstsize(t_list *lst)
{
	int	nodes;

	nodes = 0;
	while (lst)
	{
		lst = lst->next;
		nodes++;
	}
	return (nodes);
}
