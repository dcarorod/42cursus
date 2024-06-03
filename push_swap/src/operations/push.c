/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:33:01 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/01 12:33:03 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

void	pa(t_stack *a, t_stack *b)
{
	ft_push(a, ft_pop(b));
	ft_printf("pa\n");
}

void	pb(t_stack *a, t_stack *b)
{
	ft_push(b, ft_pop(a));
	ft_printf("pb\n");
}
