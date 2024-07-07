/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:19:14 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/27 15:41:36 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int	fdf_count_line_elements(const char *line)
{
	int	count;
	int	in_element;

	count = 0;
	in_element = 0;
	while (*line)
	{
		if (*line == ' ')
			in_element = 0;
		else if (!in_element)
		{
			in_element = 1;
			count++;
		}
		line++;
	}
	return (count);
}

int	**allocate_matrix(int width, int height)
{
	int	**matrix;
	int	i;

	matrix = malloc(sizeof(int *) * height);
	if (!matrix)
		return (NULL);
	i = 0;
	while (i < height)
	{
		matrix[i] = malloc(sizeof(int) * width);
		if (!matrix[i])
		{
			while (i > 0)
				free(matrix[--i]);
			free(matrix);
			return (NULL);
		}
		i++;
	}
	return (matrix);
}

static int	is_valid_color(const char *str)
{
	int	i;

	if (str[0] != '0' || (str[1] != 'x' && str[1] != 'X'))
		return (FALSE);
	i = 2;
	while (str[i] && str[i] != ' ')
	{
		if (!ft_isxdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (i > 2 && i <= 8);
}

int	is_valid_element(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (FALSE);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == ',')
	{
		i++;
		if (!is_valid_color(&str[i]))
			return (FALSE);
		while (str[i] && str[i] != ' ')
			i++;
	}
	return (str[i] == '\0' || str[i] == ' ');
}

int	validate_elements(const char *line)
{
	int			in_element;
	const char	*start;

	in_element = 0;
	while (*line)
	{
		if (*line == ' ')
		{
			in_element = 0;
			line++;
		}
		else if (!in_element)
		{
			start = line;
			in_element = 1;
			while (*line && *line != ' ')
				line++;
			if (!is_valid_element(start))
				return (FALSE);
		}
		else
			line++;
	}
	return (TRUE);
}
