/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proton <proton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:16:05 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/27 18:38:58 by proton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd_error(char *arg, int flag)
{
	char			*msg;

	if (flag == 1)
		msg = "Not a directory\n";
	else
		msg = "No such file or directory\n";
	write (2, "miniHELL: cd: ", 14);
	ft_putstr_fd(arg, 2);
	write (2, ": ", 2);
	ft_putstr_fd(msg, 2);
	return (1);
}

int	new_oldpwd(t_global *glob, char *opwd, char *dir)
{
	char	**args;

	args = (char **)malloc(sizeof(char *) * 3);
	if (!args)
		exit (1);
	args[0] = ft_strjoin("OLDPWD=", opwd);
	if (!args[0])
		exit (1);
	args[1] = ft_strjoin("PWD=", dir);
	if (!args[1])
		exit (1);
	args[2] = NULL;
	handle_cd_change(glob, args);
	ft_free_split(args);
	return (0);
}

int	handle_simple_cd(t_hashmap *map, t_global *glob)
{
	char		dir[1024];
	char		*str;
	const char	*home_dir;

	str = getcwd(dir, sizeof(dir) - 1);
	if (!str)
		return (1);
	hashmap_insert(map, "OLDPWD", str, ENV_EXP);
	home_dir = hashmap_get(map, "HOME");
	chdir((char *)home_dir);
	hashmap_insert(map, "PWD", home_dir, ENV_EXP);
	new_oldpwd(glob, str, (char *)home_dir);
	search_to_add(glob, (char *)home_dir, 5);
	search_to_add(glob, str, 8);
	return (0);
}

int	ft_change_dir(char *arg, char *oldpwd, t_global *glob)
{
	char	dir[1024];
	char	*str;

	hashmap_insert(glob->hashmap, "OLDPWD", oldpwd, ENV_EXP);
	chdir(arg);
	str = getcwd(dir, sizeof(dir) - 1);
	if (!str)
		return (1);
	hashmap_insert(glob->hashmap, "PWD", str, ENV_EXP);
	new_oldpwd(glob, oldpwd, str);
	search_to_add(glob, str, 5);
	search_to_add(glob, oldpwd, 8);
	return (0);
}

/*s_ireg == is a file, s_isdir == is a directory*/
int	ms_cd(char **arg, t_global *glob)
{
	struct stat		stat_buf;
	char			dir[1024];
	char			*str;

	str = getcwd(dir, sizeof(dir) - 1);
	if (!str)
		return (1);
	if (arg[1] == NULL || (arg[1][0] == '~'
		&& arg[1][1] == '\0' && arg[2] == NULL))
		handle_simple_cd(glob->hashmap, glob);
	else if (stat(arg[1], &stat_buf) == 0)
	{
		if (S_ISREG(stat_buf.st_mode))
			return (cd_error(arg[1], 1));
		else if (S_ISDIR(stat_buf.st_mode))
			ft_change_dir(arg[1], str, glob);
	}
	else
		return (cd_error(arg[1], 0));
	return (0);
}
