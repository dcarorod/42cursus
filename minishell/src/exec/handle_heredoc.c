/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bproton <bproton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 01:48:02 by proton            #+#    #+#             */
/*   Updated: 2024/10/02 15:00:40 by bproton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	open_heredoc(t_redir *dir)
{
	char	*heredoc;
	int		fd;

	heredoc = NULL;
	fd = open("/tmp/heredoctmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	ft_heredoc_test();
	get_heredoc_line(heredoc, fd, dir);
	close (fd);
}

void	redir_with_heredoc(t_redir *dir)
{
	int	fd;

	(void)dir;
	fd = open("/tmp/heredoctmp", O_RDONLY, 0644);
	if (fd == -1)
		return ;
	dup2(fd, STDIN_FILENO);
	close (fd);
}

int	handle_heredocuments(t_ast *root)
{
	t_redir	*temp;

	if (root->left)
		handle_heredocuments(root->left);
	if (root->right)
		handle_heredocuments(root->right);
	if (root->redir)
	{
		temp = root->redir;
		while (temp)
		{
			if (temp->type == HEREDOC)
			{
				open_heredoc(temp);
				if (root->cmd)
					root->cmd->has_heredoc = 1;
			}
			temp = temp->next;
		}
	}
	return (0);
}

int	check_num_heredoc(t_ast *root)
{
	int		heredoc;
	t_redir	*temp;

	heredoc = 0;
	if (root->left)
		handle_heredocuments(root->left);
	if (root->right)
		handle_heredocuments(root->right);
	if (root->redir)
	{
		temp = root->redir;
		while (temp)
		{
			if (temp->type == HEREDOC)
				heredoc += 1;
			temp = temp->next;
		}
	}
	return (heredoc);
}
