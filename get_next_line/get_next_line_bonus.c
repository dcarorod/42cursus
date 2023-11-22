/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:33:32 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/11/22 11:14:09 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_free_node(t_file **head, int fd)
{
	t_file	*prev;
	t_file	*current;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->content);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
	return (NULL);
}

static	t_file	*get_file(t_file **head, int fd)
{
	t_file	*current;
	t_file	*new_node;

	current = *head;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	new_node = malloc(sizeof(t_file));
	if (!new_node)
	{
		ft_free_node(head, fd);
		return (NULL);
	}
	new_node->fd = fd;
	new_node->content = NULL;
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

static char	*read_from_fd(int fd, char *content)
{
	int		bytes_read;
	char	*buffer;

	bytes_read = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free_str(&content));
	buffer[0] = '\0';
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read (fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			content = ft_strjoin(content, buffer);
		}
	}
	free(buffer);
	if (bytes_read < 0)
		return (ft_free_str(&content));
	return (content);
}

static char	*process_content(char *content)
{
	char	*buffer;
	char	*newline_pos;
	int		len;

	newline_pos = ft_strchr(content, '\n');
	if (!newline_pos)
	{
		buffer = NULL;
		return (ft_free_str(&content));
	}
	else
		len = (newline_pos - content) + 1;
	if (!content[len])
		return (ft_free_str(&content));
	buffer = ft_substr(content, len, ft_strlen(content) - len);
	ft_free_str(&content);
	if (!buffer)
		return (NULL);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static t_file	*head;
	t_file			*file;
	char			*line;
	char			*newline_pos;
	int				len;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE < 1 || !(get_file(&head, fd)))
		return (NULL);
	file = get_file(&head, fd);
	if ((file->content && !ft_strchr(file->content, '\n')) || !file->content)
		file->content = read_from_fd(fd, file->content);
	if (!file->content)
		return (ft_free_node(&head, fd));
	newline_pos = ft_strchr(file->content, '\n');
	len = (newline_pos - file->content) + 1;
	line = ft_substr(file->content, 0, len);
	if (!line)
	{
		ft_free_node(&head, fd);
		return (ft_free_str(&file->content));
	}
	file->content = process_content(file->content);
	if (!file->content || !file->content[0])
		ft_free_node(&head, fd);
	return (line);
}
