/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maximum.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:28:26 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/01 12:28:51 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

/* Find the maximum value in the stack */
int	find_max(t_stack *stack)
{
	t_node	*temp;
	int		max;

	if (stack->size <= 0)
		error_exit();
	temp = stack->top;
	max = temp->value;
	while (temp)
	{
		if (temp->value > max)
			max = temp->value;
		temp = temp->next;
	}
	return (max);
}

int	find_max_position(t_stack *stack, int max)
{
	t_node	*temp;
	int		pos;

	temp = stack->top;
	pos = 0;
	while (temp)
	{
		if (temp->value == max)
			break ;
		pos++;
		temp = temp->next;
	}
	return (pos);
}

void	move_max_to_top(t_stack *b, int position)
{
	int	i;
	int	size;

	i = 0;
	size = b->size;
	if (position <= size / 2)
	{
		while (i < position)
		{
			rb(b);
			i++;
		}
	}
	else
	{
		while (i < size - position)
		{
			rrb(b);
			i++;
		}
	}
}

void	push_max_to_a(t_stack *a, t_stack *b)
{
	int	max;
	int	position;

	max = find_max(b);
	position = find_max_position(b, max);
	move_max_to_top(b, position);
	pa(a, b);
}
