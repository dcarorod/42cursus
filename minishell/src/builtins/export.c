/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 08:11:10 by proton            #+#    #+#             */
/*   Updated: 2024/10/03 11:31:07 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export_error_message(char *arg)
{
	write (2, "miniHELL: export: `", 19);
	ft_putstr_fd(arg, 2);
	write (2, "': not a valid identifier\n", 26);
	return (4);
}

/*checks if the first character is an underscore or a
letter caps or non caps return -1 if
not in the spectrum, search where should the var be
displayed : ENV_EXP or only EXPORT*/
int	parse_export_args(char *arg)
{
	int	i;

	if (!(arg[0] == '_' || (arg[0] >= 'A' && arg[0] <= 'Z')
			|| (arg[0] >= 'a' && arg[0] <= 'z')))
		return (-1);
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '=')
			return (ENV_EXP);
	}
	return (EXPORT);
}

/*check if flag == EXPORT if the variable exists in the env
 (even in the local variables),
if it does, export the varible and set it to EXP_VAR */
static int	handle_args(char *arg, t_hashmap *map, int flag, char **str)
{
	if (flag == ENV_EXP)
	{
		str = ft_split(arg, '=');
		if (!str)
			return (1);
	}
	if (flag == ENV_EXP)
	{
		if (str[1] != NULL)
			hashmap_insert(map, str[0], str[1], ENV_EXP);
		else if (!str[1])
			hashmap_insert(map, str[0], "", ENV_EXP);
	}
	else if (flag == EXPORT)
	{
		if (hashmap_get(map, arg))
			return (0);
		else
			hashmap_insert(map, arg, "", EXPORT);
	}
	if (str)
		ft_free_split(str);
	return (0);
}

int	sort_export(t_hashmap *map)
{
	t_env_vault	*vault;

	vault = hashmap_to_vault(map);
	if (!vault)
		return (1);
	vault_sort(vault);
	vault_print_export(vault);
	vault_free(vault);
	return (0);
}

int	ms_export(char **args, t_hashmap *map, t_ast *root)
{
	int		i;
	int		error;
	int		parse_flag;
	char	**str;

	error = 0;
	parse_flag = 0;
	str = NULL;
	if (root->cmd->arg_count == 1)
		return (sort_export(map));
	i = 0;
	while (++i < root->cmd->arg_count)
	{
		parse_flag = parse_export_args(args[i]);
		if (parse_flag == EXPORT)
			handle_args(args[i], map, EXPORT, str);
		else if (parse_flag == ENV_EXP)
			handle_args(args[i], map, ENV_EXP, str);
		else
			error = export_error_message(args[i]);
	}
	if (error == 4)
		return (1);
	return (0);
}
