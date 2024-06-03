/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:37:35 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/01 12:37:55 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

// Helper function to convert stack to array
int	*stack_to_array(t_stack *stack)
{
	int		*arr;
	t_node	*current;
	int		i;

	arr = malloc(stack->size * sizeof(int));
	current = stack->top;
	i = 0;
	while (current)
	{
		arr[i] = current->value;
		current = current->next;
		i++;
	}
	return (arr);
}

// Simple bubble sort to sort the array
void	bubble_sort(int *arr, int size)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

// Function to find multiple pivots for partitioning
int	*find_pivots(t_stack *a, int num_pivots)
{
	int	*pivots;
	int	*sorted_values;
	int	i;
	int	step;

	sorted_values = stack_to_array(a);
	bubble_sort(sorted_values, a->size);
	pivots = malloc(sizeof(int) * num_pivots);
	step = a->size / (num_pivots + 1);
	i = 0;
	while (i < num_pivots)
	{
		pivots[i] = sorted_values[(i + 1) * step];
		i++;
	}
	free(sorted_values);
	return (pivots);
}

void	partition_stack(t_stack *a, t_stack *b, int *pivots, int num_pivots)
{
	int	i;
	int	j;
	int	initial_size;

	j = 0;
	while (j < num_pivots)
	{
		initial_size = a->size;
		i = 0;
		while (i < initial_size)
		{
			if (a->top->value < pivots[j])
				pb(a, b);
			else
				ra(a);
			i++;
		}
		j++;
	}
}

void	sort_stack(t_stack *a, t_stack *b)
{
	int	*pivots;
	int	num_pivots;
	int	initial_size;

	if (is_sorted(a))
		return ;
	if (a->size <= 5)
	{
		sort_small(a, b);
		return ;
	}
	initial_size = a->size;
	if (initial_size <= 10)
		num_pivots = 1;
	else if (initial_size > 10 && initial_size <= 100)
		num_pivots = 4;
	else
		num_pivots = 8;
	pivots = find_pivots(a, num_pivots);
	partition_stack(a, b, pivots, num_pivots);
	sort_stack(a, b);
	while (b->size > 0)
		push_max_to_a(a, b);
	free(pivots);
}
