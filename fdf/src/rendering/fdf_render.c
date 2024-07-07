/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:36:55 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/27 09:55:54 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static t_point	create_point(t_fdf *fdf, int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = fdf->map->z_mt[y][x];
	if (fdf->monochrome)
		point.color = FDF_MONOCHROME_COLOR;
	else if (fdf->map->iscolor && y < fdf->map->height && x < fdf->map->width)
		point.color = fdf->map->colors[y][x];
	else
	{
		if (point.z == 0)
			point.color = FDF_FLAT_COLOR;
		else
			point.color = FDF_ELEVATION_COLOR;
	}
	return (point);
}

static void	draw_horizontal_lines(t_fdf *fdf, int x, int y)
{
	t_point	start;
	t_point	end;

	start = create_point(fdf, x, y);
	end = create_point(fdf, x + 1, y);
	fdf_draw_line(fdf, start, end);
}

static void	draw_vertical_lines(t_fdf *fdf, int x, int y)
{
	t_point	start;
	t_point	end;

	start = create_point(fdf, x, y);
	end = create_point(fdf, x, y + 1);
	fdf_draw_line(fdf, start, end);
}

// Draw the line to the right neighbor: if (x < fdf->map->width - 1)
// Draw the line to the bottom neighbor if (y < fdf->map->height - 1)
void	fdf_draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	ft_bzero(fdf->img.addr, WIN_WIDTH * WIN_HEIGHT * (fdf->img.bpp / 8));
	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (x < fdf->map->width - 1)
				draw_horizontal_lines(fdf, x, y);
			if (y < fdf->map->height - 1)
				draw_vertical_lines(fdf, x, y);
			x++;
		}
		y++;
	}
}

int	fdf_render(t_fdf *fdf)
{
	if (!fdf || !fdf->mlx_ptr || !fdf->win_ptr)
		return (0);
	fdf_draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img.img_ptr, 0, 0);
	fdf_draw_menu(fdf);
	return (1);
}
