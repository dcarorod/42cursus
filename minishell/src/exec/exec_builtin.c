/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proton <proton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:45:05 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/09/27 18:39:01 by proton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_child_builtin(t_ast *root)
{
	if (ft_strcmp(root->cmd->args[0], "echo") == 0)
		return (0);
	else if (ft_strcmp(root->cmd->args[0], "pwd") == 0)
		return (0);
	else if (ft_strcmp(root->cmd->args[0], "env") == 0)
		return (0);
	else if (ft_strcmp(root->cmd->args[0], "exit") == 0)
		return (0);
	else if (ft_strcmp(root->cmd->args[0], "cd") == 0)
		return (0);
	else if (ft_strcmp(root->cmd->args[0], "unset") == 0)
		return (0);
	else if (ft_strcmp(root->cmd->args[0], "export") == 0)
		return (0);
	else
		return (1);
}

int	reset_all_fds(t_ast *root)
{
	if (root->redir)
	{
		if (root->redir->type == HEREDOC)
			root->redir = root->redir->next;
		if (root->redir->type == REDIR_IN)
		{
			dup2(root->redir->fd, STDIN_FILENO);
			close (root->redir->fd);
		}
		else if (root->redir->type == REDIR_OUT || root->redir->type == APPEND)
		{
			dup2(root->redir->fd, STDOUT_FILENO);
			close (root->redir->fd);
		}
	}
	return (-1);
}

int	exec_builtin(t_ast *root, char **args, t_global *glob)
{
	int	return_status;

	return_status = 0;
	if (root->redir)
		exec_redir(root->redir);
	if (ft_strcmp(args[0], "echo") == 0)
		return_status = ms_echo(args, glob);
	else if (ft_strcmp(args[0], "pwd") == 0)
		return_status = ms_pwd();
	else if (ft_strcmp(args[0], "env") == 0)
		return_status = ms_env(glob->env_arr);
	else if (ft_strcmp(args[0], "exit") == 0)
		return_status = ms_exit(args, glob, root);
	else if (ft_strcmp(args[0], "cd") == 0)
		return_status = ms_cd(args, glob);
	else if (ft_strcmp(args[0], "unset") == 0)
		return_status = ms_unset(args, glob->hashmap, glob);
	else if (ft_strcmp(args[0], "export") == 0)
	{
		return_status = ms_export(args, glob->hashmap, root);
		glob->env_arr = resize_env_array(glob->hashmap,
				glob, args, EXP);
	}
	reset_all_fds(root);
	return (return_status);
}
