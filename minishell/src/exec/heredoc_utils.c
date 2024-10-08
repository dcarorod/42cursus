/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bproton <bproton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:50:01 by bproton           #+#    #+#             */
/*   Updated: 2024/10/02 14:56:17 by bproton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_heredoc_putstr(char *str, int fd)
{
	int	i;

	i = -1;
	while (str[++i])
		write (fd, &str[i], 1);
	write (fd, "\n", 1);
}

void	get_heredoc_line(char *heredoc, int fd, t_redir *dir)
{
	while (1)
	{
		heredoc = readline("> ");
		if (g_signal_status == 1)
		{
			close (fd);
			unlink("/tmp/heredoctmp");
			return ;
		}
		if (!heredoc)
		{
			ft_putstr_fd(ERROR_HEREDOC, 2);
			ft_putstr_fd(dir->file, 2);
			write (2, "')\n", 3);
			return ;
		}
		if (ft_strcmp(heredoc, dir->file) == 0)
		{
			free (heredoc);
			return ;
		}
		ft_heredoc_putstr(heredoc, fd);
		free (heredoc);
	}
}
