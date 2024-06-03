/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:30:22 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/01 12:30:25 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

/* Validate if the string is a valid integer */
int	is_valid_integer(char *str)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	if (!ft_isdigit(*str))
		return (0);
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		if ((sign == 1 && result > FT_INT_MAX)
			|| (sign == -1 && - result < FT_INT_MIN))
			return (0);
		str++;
	}
	return (*str == '\0');
}

int	has_dups(int *array, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (array[i] == array[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	parse_input(int argc, char **argv, t_stack *a)
{
	int	i;
	int	*values;

	values = malloc((argc - 1) * sizeof(int));
	if (!values)
		error_exit();
	i = 1;
	while (i < argc)
	{
		if (!is_valid_integer(argv[i]))
			free_and_exit(values);
		values[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	if (has_dups(values, argc - 1))
		free_and_exit(values);
	i = argc - 2;
	while (i >= 0)
	{
		ft_push(a, values[i]);
		i--;
	}
	free(values);
}

void	print_stack(t_stack *stack)
{
	t_node	*current;

	current = stack->top;
	while (current)
	{
		ft_printf("%d ", current->value);
		current = current->next;
	}
	ft_printf("\n");
}
