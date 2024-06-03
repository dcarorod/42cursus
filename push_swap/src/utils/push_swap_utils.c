/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:30:32 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/01 12:30:47 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

t_stack	*init_stack(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		error_exit();
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
	return (stack);
}

int	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (stack->size < 2)
		return (1);
	current = stack->top;
	while (current && current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

void	error_exit(void)
{
	ft_printf("Error\n");
	exit(EXIT_FAILURE);
}

void	free_and_exit(void *ptr)
{
	free(ptr);
	error_exit();
}

void	free_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*next;

	current = stack->top;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(stack);
}
