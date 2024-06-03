/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:37:10 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/01 12:51:23 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

/* Sort a stack of three integers */
void	sort_three(t_stack *a)
{
	int	top;
	int	mid;
	int	bot;

	top = a->top->value;
	mid = a->top->next->value;
	bot = a->bottom->value;
	if (top > mid && mid < bot && top < bot)
		sa(a);
	else if (top < mid && mid > bot && top < bot)
	{
		rra(a);
		sa(a);
	}
	else if (top < mid && mid > bot && top > bot)
		rra(a);
	else if (top > mid && mid < bot && top > bot)
		ra(a);
	else if (mid < top && mid > bot && top > bot)
	{
		sa(a);
		rra(a);
	}
}

void	sort_small(t_stack *a, t_stack *b)
{
	if (is_sorted(a) || a->size <= 1 || a->size > 5)
		return ;
	if (a->size == 2 && a->top->value > a->top->next->value)
		sa(a);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size == 4)
	{
		push_min_to_b(a, b);
		sort_three(a);
		pa(a, b);
	}
	else
	{
		push_min_to_b(a, b);
		push_min_to_b(a, b);
		sort_three(a);
		pa(a, b);
		pa(a, b);
	}
}
