/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:33:41 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/01 12:33:43 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

void	sa(t_stack *a)
{
	ft_swap(a);
	ft_printf("sa\n");
}

void	sb(t_stack *b)
{
	ft_swap(b);
	ft_printf("sb\n");
}

void	ss(t_stack *a, t_stack *b)
{
	ft_swap(a);
	ft_swap(b);
	ft_printf("ss\n");
}
