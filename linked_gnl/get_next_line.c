/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:13:03 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/11/20 21:43:52 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
static void	ft_free_node(t_file **head, t_file *node)
{
	t_file	*temp;

	if (*head == node)
	{
		temp = node;
		*head = (*head)->next;
		free(temp);
	}
	else
	{
		temp = *head;
		while (temp)
		{
			if (temp->next == node)
			{
				temp->next = node->next;
				break ;
			}
			temp = temp->next;
		}
		free(node);
	}
}
*/

static void	ft_free_node(t_file **head, t_file *node)
{
	t_file	*temp;
	t_file	*prev;

	if (*head == NULL || node == NULL)
		return ;
	if (*head == node)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->data);
		free(temp);
		return ;
	}
	temp = *head;
	while (temp && temp != node)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free(temp->data);
	free(temp);
}

static t_file	*ft_get_node(int fd, t_file **head)
{
	t_file	*current;
	t_file	*last;

	current = *head;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		last = current;
		current = current->next;
	}
	current = malloc(sizeof(t_file));
	if (!current)
		return (NULL);
	current->fd = fd;
	current->data = NULL;
	current->next = NULL;
	if (!(*head))
		*head = current;
	else
		last->next = current;
	return (current);
}

static int	read_from_fd(int fd, t_file *file, char *buffer)
{
	int		bytes_read;
	char	*newline_pos;

	newline_pos = NULL;
	bytes_read = 1;
	while (!newline_pos && bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (-1);
		buffer[bytes_read] = '\0';
		file->data = ft_strjoin(file->data, buffer);
		if (!file->data)
		{
			free(buffer);
			return (-1);
		}
		newline_pos = ft_strchr(file->data, '\n');
	}
	free(buffer);
	return (bytes_read);
}

static int	append_line(int fd, t_file *file)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	bytes_read = read_from_fd(fd, file, buffer);
	free(buffer);
	if (bytes_read < 0)
		return (-1);
	if (bytes_read || ft_strlen(file->data))
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_file	*head;
	t_file			*file;
	char			*newline_pos;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	file = ft_get_node(fd, &head);
	if (!file)
		return (NULL);
	if (append_line(fd, file) <= 0)
		return (NULL);
	newline_pos = ft_strchr(file->data, '\n');
	if (newline_pos || (!newline_pos && ft_strlen(file->data) > 0))
	{
		if (newline_pos)
			*newline_pos = '\0';
		line = ft_strjoin(file->data, "\n");
		ft_strcpy(file->data, ++newline_pos);
	}
	else
		line = ft_strdup("");
	if (!file->data || !(*file->data))
	{
		ft_free_node(&head, file);
		file = NULL;
	}
	return (line);
}


/*
char	*get_next_line(int fd)
{
	static t_file	*head;
	t_file			*file;
	char			*newline_pos;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	file = ft_get_node(fd, &head);
	if (!file)
		return (NULL);
	if (append_line(fd, file) <= 0)
		return (NULL);
	newline_pos = ft_strchr(file->data, '\n');
	if (newline_pos)
	{
		*newline_pos = '\0';
		line = ft_strdup(file->data);
		ft_strcpy(file->data, ++newline_pos);
	}
	else
		line = ft_strdup(file->data);
	if (!(*file->data))
	{
		ft_free_node(&head, file);
		file = NULL;
	}
	return (line);
}
*/
