/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_fill_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:34:08 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/25 18:24:16 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static int	**init_colors(int width, int height)
{
	int		x;
	int		y;
	int		**colors;

	colors = allocate_matrix(width, height);
	if (!colors)
		return (NULL);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			colors[y][x] = FDF_DEFAULT_COLOR;
			x++;
		}
		y++;
	}
	return (colors);
}

t_map	*fdf_initialize_map(int width, int height)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = width;
	map->height = height;
	map->min_z = FT_INT_MAX;
	map->max_z = FT_INT_MIN;
	map->iscolor = FALSE;
	map->z_mt = allocate_matrix(width, height);
	if (!map->z_mt)
		return (fdf_free_and_null(map));
	map->colors = init_colors(width, height);
	if (!map->colors)
	{
		fdf_free_matrix(map->z_mt, height);
		return (fdf_free_and_null(map));
	}
	return (map);
}

static int	process_element(t_map *map, char *element, int x, int y)
{
	char	*comma_ptr;
	int		elevation;
	int		color;

	comma_ptr = ft_strchr(element, ',');
	if (comma_ptr)
	{
		color = fdf_hex_to_int(comma_ptr + 1);
		map->iscolor = TRUE;
		*comma_ptr = '\0';
		elevation = ft_atoi(element);
		*comma_ptr = ',';
	}
	else
	{
		elevation = ft_atoi(element);
		color = FDF_DEFAULT_COLOR;
	}
	map->z_mt[y][x] = elevation;
	map->colors[y][x] = color;
	if (elevation < map->min_z)
		map->min_z = elevation;
	if (elevation > map->max_z)
		map->max_z = elevation;
	return (TRUE);
}

static int	parse_map_line(char *line, t_map *map, int width, int y)
{
	char	**elements;
	int		count;

	elements = ft_split(line, ' ');
	if (!elements)
		return (FALSE);
	count = 0;
	while (elements[count])
	{
		if (!is_valid_element(elements[count]) || count >= width
			|| !process_element(map, elements[count], count, y))
		{
			ft_free_split(elements);
			return (FALSE);
		}
		count++;
	}
	if (count != width)
	{
		ft_free_split(elements);
		return (FALSE);
	}
	ft_free_split(elements);
	return (TRUE);
}

t_map	*fdf_fill_map(char **lines, int height, int width)
{
	t_map	*map;
	int		y;

	if (!lines || height < 1 || width < 1)
		return (NULL);
	map = fdf_initialize_map(width, height);
	if (!map)
		return (fdf_cleanup_null(lines, (void (*)(void *))ft_free_split));
	y = 0;
	while (lines[y])
	{
		if (!validate_elements(lines[y])
			|| !parse_map_line(lines[y], map, width, y))
			return (fdf_cleanup(map, lines));
		y++;
	}
	ft_free_split(lines);
	return (map);
}
