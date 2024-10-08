/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proton <proton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 08:05:19 by bproton           #+#    #+#             */
/*   Updated: 2024/09/27 14:33:23 by proton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_left_right(int fd[2], t_ast *root, t_global *glob, int flag)
{
	if (flag == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		start_exec(root->left, glob, 0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		start_exec(root->right, glob, 0);
	}
	return (0);
}

static int	close_n_waitpid(int fd[2], int pid1, int pid2)
{
	int	status;

	close (fd[1]);
	close (fd[0]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (0);
}

static int	handle_pipes(t_ast *root, t_global *glob)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == -1)
		return (1);
	if (pid1 == 0)
	{
		handle_left_right(fd, root, glob, 0);
		exit (0);
	}
	pid2 = fork();
	if (pid2 == -1)
		return (1);
	if (pid2 == 0)
	{
		handle_left_right(fd, root, glob, 1);
		exit (0);
	}
	return (close_n_waitpid(fd, pid1, pid2));
}

char	*handle_type_cmd(t_ast *root, t_global *glob)
{
	int		exec_status;
	char	*for_exit;

	exec_status = 0;
	if (is_child_builtin(root) == 0)
	{
		if (exec_builtin(root, root->cmd->args, glob))
			exec_status = 1;
		else
			exec_status = 0;
	}
	else
		exec_status = exec_cmd(root, root->cmd, glob);
	for_exit = ft_itoa(exec_status);
	if (!for_exit)
		return (NULL);
	return (for_exit);
}

int	start_exec(t_ast *root, t_global *glob, int heredoc)
{
	char	*exit_status;

	if (glob->lex_head->has_heredoc && heredoc)
	{
		handle_heredocuments(root);
		heredoc -= heredoc;
	}
	if (root->type == AST_CMD)
	{
		exit_status = handle_type_cmd(root, glob);
		if (!exit_status)
			return (1);
		hashmap_insert(glob->hashmap, "?", exit_status, QMARK);
		free (exit_status);
	}
	else if (root->type == AST_PIPE)
		handle_pipes(root, glob);
	return (0);
}
