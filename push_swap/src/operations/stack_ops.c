/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:32:49 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/01 12:32:52 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

/* Pop a value from the stack */
int	ft_pop(t_stack *stack)
{
	t_node	*top_node;
	int		value;

	if (!stack->top)
		return (-1);
	top_node = stack->top;
	value = top_node->value;
	stack->top = top_node->next;
	if (stack->top)
		stack->top->prev = NULL;
	else
		stack->bottom = NULL;
	free(top_node);
	stack->size--;
	return (value);
}

/* Push a value onto the stack */
void	ft_push(t_stack *stack, int value)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		error_exit();
	new_node->value = value;
	new_node->prev = NULL;
	new_node->next = stack->top;
	if (stack->top)
		stack->top->prev = new_node;
	stack->top = new_node;
	if (!stack->bottom)
		stack->bottom = new_node;
	stack->size++;
}

// Swap the top two elements of the stack
void	ft_swap(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	if (stack->size < 2)
		return ;
	first = stack->top;
	second = stack->top->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	second->next = first;
	first->prev = second;
	second->prev = NULL;
	stack->top = second;
	if (stack->size == 2)
		stack->bottom = first;
}

/* Rotate the stack upwards */
void	ft_rotate(t_stack *stack)
{
	t_node	*first;

	if (stack->size < 2)
		return ;
	first = stack->top;
	stack->top = first->next;
	stack->top->prev = NULL;
	first->next = NULL;
	first->prev = stack->bottom;
	stack->bottom->next = first;
	stack->bottom = first;
}

/* Reverse rotate the stack downwards */
void	ft_reverse_rotate(t_stack *stack)
{
	t_node	*last;

	if (stack->size < 2)
		return ;
	last = stack->bottom;
	stack->bottom = last->prev;
	stack->bottom->next = NULL;
	last->prev = NULL;
	last->next = stack->top;
	stack->top->prev = last;
	stack->top = last;
}
