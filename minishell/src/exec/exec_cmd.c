/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:13:39 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/10/02 15:33:07 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_get_path(t_hashmap *map, char **arg)
{
	const char	*path;

	path = NULL;
	path = hashmap_get(map, "PATH");
	if (!path)
	{
		write (2, "miniHELL: ", 10);
		ft_putstr_fd(arg[0], 2);
		write (2, ": No such file or directory\n", 28);
		exit (127);
	}
	return ((char *)path);
}

static char	*research_path(char *path, char *cmd)
{
	int		j;
	char	**cmd_path;
	char	*temp;

	cmd_path = ft_split_path(path, ':');
	j = -1;
	while (cmd_path[++j])
	{
		temp = ft_strjoin(cmd_path[j], cmd);
		if (access(temp, F_OK | X_OK) == 0)
		{
			ft_free_split(cmd_path);
			return (temp);
		}
		free(temp);
	}
	if (!temp)
		print_error_cmd(path);
	ft_free_split(cmd_path);
	print_error_cmd(cmd);
	return (NULL);
}

static int	make_cmd(char **arg, t_global *glob)
{
	char	*path;
	char	*new_path;

	if (arg[0][0] == '/' && (access(arg[0], F_OK | X_OK) != 0))
	{
		write (2, "miniHELL: ", 10);
		ft_putstr_fd(arg[0], 2);
		write (2, ": Not directory\n", 16);
		exit (126);
	}
	if (access(arg[0], F_OK | X_OK) == 0)
	{
		if (execve(arg[0], arg, glob->absolute_path) == -1)
			exit(126);
	}
	path = ft_get_path(glob->hashmap, arg);
	new_path = research_path(path, arg[0]);
	if (!new_path)
		exit (127);
	if (execve(new_path, arg, glob->env_arr) == -1)
	{
		free (new_path);
		exit(127);
	}
	return (0);
}

static int	return_parent(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}

int	exec_cmd(t_ast *root, t_command *cmd, t_global *glob)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		setup_child_signals();
		if (root->redir)
		{
			if (cmd->has_heredoc == 1 && g_signal_status != 1)
				redir_with_heredoc(root->redir);
			if (g_signal_status == 1)
				exit (130);
			if (exec_redir(root->redir))
				exit (EXIT_FAILURE);
		}
		make_cmd(cmd->args, glob);
		exit(EXIT_SUCCESS);
	}
	else
		return (return_parent(pid));
}
