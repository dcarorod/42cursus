/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proton <proton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:39:05 by bproton           #+#    #+#             */
/*   Updated: 2024/09/27 18:39:04 by proton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_all_fds(t_ast *root)
{
	t_redir	*temp;

	if (root->left)
		close_all_fds(root->left);
	if (root->right)
		close_all_fds(root->right);
	if (root->redir)
	{
		temp = root->redir;
		while (temp)
		{
			if (temp->fd != -1)
				close (temp->fd);
			temp = temp->next;
		}
	}
}

int	handle_redir_in(t_redir *dir)
{
	int	fd;

	fd = open(dir->file, O_RDONLY, 0644);
	if (fd == -1)
	{
		write (2, "miniHELL: ", 10);
		ft_putstr_fd(dir->file, 2);
		write (2, ": No such file or directory\n", 28);
		return (1);
	}
	dir->fd = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close (fd);
	return (0);
}

int	handle_redir_out(t_redir *dir)
{
	int	fd;

	fd = open(dir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	dir->fd = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close (fd);
	return (0);
}

int	handle_append(t_redir *dir)
{
	int	fd;

	fd = open(dir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	dir->fd = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close (fd);
	return (0);
}

int	exec_redir(t_redir *dir)
{
	while (dir)
	{
		if (dir->type == REDIR_IN)
		{
			if (handle_redir_in(dir) == 1)
				return (1);
		}
		else if (dir->type == REDIR_OUT)
			handle_redir_out(dir);
		else if (dir->type == APPEND)
			handle_append(dir);
		dir = dir->next;
	}
	return (0);
}
