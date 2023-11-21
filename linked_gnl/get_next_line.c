/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:13:03 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/11/21 10:14:38 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_free_list(t_file **to_free)
{
	t_file	*temp;

	while (*to_free)
	{
		temp = (*to_free)->next;
		free((*to_free)->data);
		free(*to_free);
		*to_free = temp;
	}
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
		ft_free_list(head);
		return (NULL);
	}
	new_node->fd = fd;
	new_node->data = NULL;
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

static char	*read_buffer(int fd, char *content)
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

static char	*handle_content(char *content)
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

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	file = get_file(&head, fd);
	if ((file->data && !ft_strchr(file->data, '\n')) || !file->data)
		file->data = read_buffer(fd, file->data);
	if (!file->data)
		return (NULL);
	newline_pos = ft_strchr(file->data, '\n');
	len = (newline_pos - file->data) + 1;
	line = ft_substr(file->data, 0, len);
	if (!line)
	{
		ft_free_list(&head);
		return (ft_free_str(&file->data));
	}
	file->data = handle_content(file->data);
	if (!file->data || !file->data[0] || !head)
		ft_free_list(&head);
	return (line);
}
