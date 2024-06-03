/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:38:34 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/01 12:47:33 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef FT_INT_MAX
#  define FT_INT_MAX 2147483647
# endif
# ifndef FT_INT_MIN
#  define FT_INT_MIN -2147483648
# endif

/* Node structure for the linked list */
typedef struct s_node
{
	int				value;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

/* Stack structure */
typedef struct s_stack
{
	t_node	*top;
	t_node	*bottom;
	int		size;
}	t_stack;

/* Stack operations */
void	push_swap(t_stack *a, t_stack *b);
int		ft_pop(t_stack *stack);
void	ft_push(t_stack *stack, int value);
void	ft_swap(t_stack *stack);
void	ft_rotate(t_stack *stack);
void	ft_reverse_rotate(t_stack *stack);

/* Perform operations */
void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);
void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);

/* Utils */
t_stack	*init_stack(void);
int		is_sorted(t_stack *stack);
void	error_exit(void);
void	free_and_exit(void *ptr);
void	free_stack(t_stack *stack);
int		is_valid_integer(char *str);
int		has_dups(int *array, int size);
void	parse_input(int argc, char **argv, t_stack *a);
void	print_stack(t_stack *stack);
int		find_min(t_stack *stack);
int		find_min_position(t_stack *stack, int min);
void	move_min_to_top(t_stack *a, int position);
void	push_min_to_b(t_stack *a, t_stack *b);
int		find_max(t_stack *stack);
int		find_max_position(t_stack *stack, int max);
void	move_max_to_top(t_stack *b, int position);
void	push_max_to_a(t_stack *a, t_stack *b);

/* Algo */
void	sort_three(t_stack *a);
void	sort_small(t_stack *a, t_stack *b);
int		*stack_to_array(t_stack *stack);
void	bubble_sort(int *arr, int size);
int		*find_pivots(t_stack *a, int num_pivots);
void	partition_stack(t_stack *a, t_stack *b, int *pivots, int num_pivots);
void	sort_stack(t_stack *a, t_stack *b);

/* Errors */
void	error_exit(void);
void	free_and_exit(void *ptr);
void	free_stack(t_stack *stack);

/* ft_printf*/
int		ft_printf(const char *format, ...);
int		ft_handle_specifier(const char f, va_list args);
int		ft_handle_char(va_list args);
int		ft_handle_str(va_list args);
int		ft_handle_int(int n);
int		ft_handle_uint(unsigned int n);
int		ft_handle_hex(va_list args, int is_upper);
int		ft_handle_ptr(va_list args);
int		ft_handle_percent(void);
int		ft_putchar(int c);
int		ft_putstr(const char *str);
int		ft_strlen(char *str);
int		ft_isformatspecifier(const char f);

/* ft_atoi */
int		ft_isdigit(int c);
int		ft_isspace(char c);
int		ft_atoi(const char *str);

#endif
