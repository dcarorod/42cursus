/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimum.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:29:07 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/01 12:29:37 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

/* Find the minimum value in the stack */
int	find_min(t_stack *stack)
{
	t_node	*temp;
	int		min;

	if (stack->size <= 0)
		error_exit();
	temp = stack->top;
	min = temp->value;
	while (temp)
	{
		if (temp->value < min)
			min = temp->value;
		temp = temp->next;
	}
	return (min);
}

int	find_min_position(t_stack *stack, int min)
{
	t_node	*temp;
	int		pos;

	temp = stack->top;
	pos = 0;
	while (temp)
	{
		if (temp->value == min)
			break ;
		pos++;
		temp = temp->next;
	}
	return (pos);
}

void	move_min_to_top(t_stack *a, int position)
{
	int	i;
	int	size;

	i = 0;
	size = a->size;
	if (position <= size / 2)
	{
		while (i < position)
		{
			ra(a);
			i++;
		}
	}
	else
	{
		while (i < size - position)
		{
			rra(a);
			i++;
		}
	}
}

void	push_min_to_b(t_stack *a, t_stack *b)
{
	int		min;
	int		position;

	min = find_min(a);
	position = find_min_position(a, min);
	move_min_to_top(a, position);
	pb(a, b);
}
