/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proton <proton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:57:01 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/26 10:43:56 by proton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_line(char **args, int flag)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			write(1, " ", 1);
	}
	if (flag == 1)
		write(1, "\n", 1);
}

int	handle_newline(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ms_echo(char **args, t_global *glob)
{
	int	i;
	int	flag;

	(void)glob;
	i = 1;
	flag = 1;
	while (args[i] && handle_newline(args[i]))
	{
		flag = 0;
		i++;
	}
	print_line(args + i, flag);
	return (0);
}
