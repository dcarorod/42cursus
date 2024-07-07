/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 12:05:40 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/25 18:25:56 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	*fdf_free_and_null(void *ptr)
{
	free(ptr);
	return (NULL);
}

void	fdf_free_matrix(int **matrix, int height)
{
	int	i;

	if (!matrix || height <= 0)
		return ;
	i = 0;
	while (i < height)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	fdf_free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->z_mt)
		fdf_free_matrix(map->z_mt, map->height);
	if (map->colors)
		fdf_free_matrix(map->colors, map->height);
	free(map);
}

void	*fdf_cleanup(t_map *map, char **split)
{
	fdf_free_map(map);
	ft_free_split(split);
	return (NULL);
}

void	*fdf_cleanup_null(void *ptr, void (*free_function)(void *))
{
	if (ptr != NULL && free_function != NULL)
		free_function(ptr);
	return (NULL);
}
