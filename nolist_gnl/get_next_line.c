/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro <dcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 21:56:00 by dcaro-ro          #+#    #+#             */
/*   Updated: 2023/11/13 13:10:27 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_buffer(int fd, char *content)
{
	int		bytes_read;
	char	*buffer;

	bytes_read = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free_str(&content));
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
		return (free_str(&content));
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
		return (free_str(&content));
	}
	else
		len = (newline_pos - content) + 1;
	if (!content[len])
		return (free_str(&content));
	buffer = ft_substr(content, len, ft_strlen(content) - len);
	free_str(&content);
	if (!buffer)
		return (NULL);
	return (buffer);
}

static char	*get_line(char *content)
{
	char	*line;
	char	*newline_pos;
	int		len;

	newline_pos = ft_strchr(content, '\n');
	len = (newline_pos - content) + 1;
	line = ft_substr(content, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*content = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((content && !ft_strchr(content, '\n')) || !content)
		content = read_buffer(fd, content);
	if (!content)
		return (NULL);
	line = get_line(content);
	if (!line)
		return (free_str(&content));
	content = handle_content(content);
	return (line);
}
