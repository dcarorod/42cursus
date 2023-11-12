/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:21:46 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/11/12 12:04:35 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_file	*get_file(t_file **head, int fd)
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
		return (NULL);
	new_node->fd = fd;
	new_node->read_data = ft_strdup("");
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

static void	free_node(t_file **node)
{
	if (*node)
	{
		free((*node)->read_data);
		free(*node);
		*node = NULL;
	}
}

static char	*get_line(t_file **file)
{
	size_t	i;
	char	*line;
	char	*temp;

	while((*file)->read_data[i] && (*file)->read_data[i] != '\n')
		i++;
	temp = (*file)->read_data;
	line = ft_substr(temp, 0, i);
	(*file)->read_data = ft_strdup(&(*file)->read_data[i + 1]);
	free(temp);
	return (line);
}

static int	read_file(t_file **file)
{
	int	bytes_read;
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;

	bytes_read = read((*file)->fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (-1);
	buffer[bytes_read] = '\0';
	temp = (*file)->read_data;
	(*file)->read_data = ft_strjoin(temp, buffer);
	free(temp);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static t_file	*head = NULL;
	t_file		*current;
	int		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	current = get_file(&head, fd);
	if (!current)
		return (NULL);
	while (!ft_strchr(current->read_data, '\n'))
	{
		bytes_read = read_file(&current);
		if (bytes_read <= 0)
		{
			if (bytes_read == 0 && current->read_data[0] == '\0')
			{
				free_node(&current);
				return (NULL);
			}
			return (NULL);
		}
	}
	if (ft_strchr(current->read_data, '\n'))
		return (get_line(&current));
	return (NULL);
}
