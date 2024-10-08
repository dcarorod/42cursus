/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 08:11:07 by proton            #+#    #+#             */
/*   Updated: 2024/10/03 11:08:12 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static long long	ft_atolonglong(const char *str)
{
	long long	i;
	long long	sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}

static long long	long_cmp(const char *s1)
{
	char	*longmax;
	char	*longmin;
	int		len;

	longmax = "9223372036854775807";
	longmin = "-9223372036854775808";
	len = ft_strlen(s1);
	if (len > 19 && s1[0] != '-')
		return (1);
	if (len > 20 && s1[0] == '-')
		return (1);
	else if (len == 19)
	{
		if (s1[0] == '-')
		{
			if (ft_strcmp(s1, longmin) > 0)
				return (1);
		}
		else
		{
			if (ft_strcmp(s1, longmax) > 0)
				return (1);
		}
	}
	return (0);
}

void	handle_non_numeric_args(char *arg, t_global *glob,
	t_ast *root, int flag)
{
	if (flag == 0)
		write (1, "exit\n", 6);
	write (2, "miniHELL: exit: ", 16);
	ft_putstr_fd(arg, 2);
	write (2, ": numeric argument required\n", 28);
	close_all_fds(root);
	free_ast(root);
	free_lexer_state(glob->lex_head);
	ft_free_split(glob->env_arr);
	ft_free_split(glob->absolute_path);
	hashmap_free(glob->hashmap);
	if (access("/tmp/heredoctmp", F_OK) == 0)
		unlink("/tmp/heredoctmp");
	glob->exit_status = 2;
	exit (2);
}

int	rest_of_exit(char **arg, t_global *glob, t_ast *root, int flag)
{
	long long int	i;

	i = 0;
	if (arg[1])
		i = ft_atolonglong(arg[1]);
	close_all_fds(root);
	free_ast(root);
	free_lexer_state(glob->lex_head);
	ft_free_split(glob->env_arr);
	ft_free_split(glob->absolute_path);
	if (access("/tmp/heredoctmp", F_OK) == 0)
		unlink("/tmp/heredoctmp");
	hashmap_free(glob->hashmap);
	if (flag == 0)
		write (1, "exit\n", 5);
	glob->exit_status = (i % 256);
	exit (i % 256);
}

int	ms_exit(char **args, t_global *glob, t_ast *root)
{
	t_index_exit	index;

	index.flag = 0;
	if (glob->lex_head->has_pipe)
		index.flag = 1;
	if (root->cmd->arg_count > 2)
	{
		write (1, "exit\n", 5);
		write (2, "miniHELL: exit: too many arguments\n", 35);
		return (1);
	}
	index.i = -1;
	if (args[1])
	{
		while (args[1][++index.i])
		{
			if ((args[1][0] == '-' || args[1][0] == '+') && index.i == 0)
				index.i++;
			if ((args[1][index.i] < 48 || args[1][index.i] > 57)
				|| long_cmp(args[1]))
				handle_non_numeric_args(args[1], glob, root, index.flag);
		}
	}
	return (rest_of_exit(args, glob, root, index.flag));
}
