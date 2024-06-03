/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:48:48 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/01 13:29:08 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	push_swap(t_stack *a, t_stack *b)
{
	if (a->size <= 5)
		sort_small(a, b);
	else
		sort_stack(a, b);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc < 2)
		return (0);
	a = init_stack();
	b = init_stack();
	parse_input(argc, argv, a);
	if (a->size == 1 || is_sorted(a))
	{
		free_stack(a);
		free_stack(b);
		return (0);
	}
	push_swap(a, b);
	free_stack(a);
	free_stack(b);
	return (0);
}

/*int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	//int	*pivots;
	//int	num_pivots;
	//int	initial_size;

	if (argc < 2)
		return (0);
	a = init_stack();
	b = init_stack();
	parse_input(argc, argv, a);
	if (a->size == 1 || is_sorted(a))
	{
		free_stack(a);
		free_stack(b);
		return (0);
	}
	ft_printf("Original stack:\n");
	ft_printf("n = %d\n", a->size);
	print_stack(a);

	//initial_size = a->size;
	//if (initial_size <= 10)
	//	num_pivots = 1;
	//else if (initial_size > 10 && initial_size <= 100)
	//	num_pivots = 4;
	//else
	//	num_pivots = 9;
	//pivots = find_pivots(a, num_pivots);
	//ft_printf("\nPivots:\n");
	//for (int i = 0; i < num_pivots; i++)
	//	ft_printf("%d ", pivots[i]);
	//ft_printf("\n");
	//ft_printf("\nPartitioning stack...\n");
	//partition_stack(a, b, pivots, num_pivots);

	//ft_printf("Stack A after partition:\n");
	//print_stack(a);
	//ft_printf("Stack B after partition:\n");
	//print_stack(b);

	ft_printf("\nSorted stack: \n");
	push_swap(a, b);
	print_stack(a);

	ft_printf("\nminimum: %d \n", find_min(a));
	free_stack(a);
	free_stack(b);
	return (0);
}
*/
