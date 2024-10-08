/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bproton <bproton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:20:00 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/29 14:12:18 by bproton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_error_cmd(char *cmd)
{
	write (2, "miniHELL: ", 10);
	ft_putstr_fd(cmd, 2);
	write (2, ": command not found\n", 20);
	exit (127);
}

void	*pfree_ast(t_ast *ast,
	const char *message, t_print_type print_type)
{
	if (ast)
	{
		ms_print_message(message, print_type);
		return (free_ast(ast));
	}
	return (NULL);
}

int	pclean_ast(t_ast *ast, const char *message,
	t_print_type print_type, int value)
{
	if (ast)
		pfree_ast(ast, message, print_type);
	return (value);
}

void	*ms_print_message(const char *message, t_print_type print_type)
{
	if (message)
	{
		if (print_type == PT_PERROR)
			perror(message);
		else if (print_type == PT_PRINTF)
			printf("%s\n", message);
		else
			printf("Invalid print type\n");
	}
	return (NULL);
}

int	ms_log_val(t_print_type print_type, const char *str, int value)
{
	ms_print_message(str, print_type);
	return (value);
}
