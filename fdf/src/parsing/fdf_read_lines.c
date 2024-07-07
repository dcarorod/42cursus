/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:21:50 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/27 15:41:45 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static char	**reallocate_lines(char **lines, int size)
{
	char	**temp;

	temp = ft_realloc(lines, sizeof(char *) * (size + FDF_BUFFER_SIZE + 1));
	if (!temp)
	{
		ft_free_split(lines);
		return (fdf_perror_null(FDF_ERROR_MALLOC));
	}
	return (temp);
}

static char	*trim_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

static int	handle_line(char *line, char ***lines, int *i, int *width)
{
	int	line_width;

	line = trim_newline(line);
	line_width = fdf_count_line_elements(line);
	if (*i == 0)
		*width = line_width;
	else if (line_width != *width)
	{
		ft_printf("Found wrong line length at line %d\n", *i + 1);
		free(line);
		return (-1);
	}
	(*lines)[(*i)++] = line;
	if (*i >= FDF_BUFFER_SIZE)
	{
		*lines = reallocate_lines(*lines, *i);
		if (!(*lines))
			return (-1);
	}
	return (0);
}

int	fdf_read_lines(int fd, char ***lines, int *width, int *flag)
{
	int		i;
	char	*line;
	int		status;

	i = 0;
	*flag = TRUE;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		status = handle_line(line, lines, &i, width);
		if (status < 0)
			*flag = FALSE;
	}
	(*lines)[i] = NULL;
	return (i);
}
