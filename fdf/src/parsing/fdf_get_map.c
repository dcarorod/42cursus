/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 12:02:47 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/27 15:40:01 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static char	**allocate_lines(void)
{
	char	**lines;

	lines = malloc(sizeof(char *) * (FDF_BUFFER_SIZE + 1));
	if (!lines)
		return (fdf_perror_null(FDF_ERROR_MALLOC));
	return (lines);
}

char	**fdf_get_file_lines(const char *filename,
	int *width, int *height, int *flag)
{
	int		fd;
	int		lines_count;
	char	**lines;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (fdf_perror_null(FDF_ERROR_OPEN));
	lines = allocate_lines();
	if (!lines)
	{
		close(fd);
		return (NULL);
	}
	lines_count = fdf_read_lines(fd, &lines, width, flag);
	close(fd);
	if (lines_count < 0)
	{
		ft_free_split(lines);
		return (NULL);
	}
	*height = lines_count;
	return (lines);
}

static void	*free_message_null(char **split, char *str)
{
	ft_free_split(split);
	ft_putstr(str);
	return (NULL);
}

t_map	*fdf_get_map(const char *filename)
{
	int		width;
	int		height;
	char	**lines;
	t_map	*map;
	int		flag;

	if (ft_strlen(filename) < 5
		|| ft_strncmp(filename + ft_strlen(filename) - 4, ".fdf", 4) != 0)
		return (fdf_perror_null(FDF_ERROR_EXTENSION));
	width = 0;
	height = 0;
	flag = 1;
	lines = fdf_get_file_lines(filename, &width, &height, &flag);
	if (!lines)
		return (fdf_perror_null(FDF_ERROR_MALLOC));
	if (!flag)
		return (free_message_null(lines, FDF_ERROR_WIDTH));
	if (width < 1 || height < 1)
		return (free_message_null(lines, "Error: invalid map dimensions\n"));
	map = fdf_fill_map(lines, height, width);
	if (!map)
		ft_free_split(lines);
	return (map);
}
