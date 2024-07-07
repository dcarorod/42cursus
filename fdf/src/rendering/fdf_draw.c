/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:02:33 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/27 12:05:26 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*px;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		px = fdf->img.addr + (y * fdf->img.size_line + x * (fdf->img.bpp / 8));
		*(unsigned int *)px = color;
	}
}

static void	init_bresenham(t_bresenham *bres, t_point start, t_point end)
{
	bres->dx = ft_abs(end.x - start.x);
	bres->dy = -ft_abs(end.y - start.y);
	bres->sx = -1;
	if (start.x < end.x)
		bres->sx = 1;
	bres->sy = -1;
	if (start.y < end.y)
		bres->sy = 1;
	bres->error = bres->dx + bres->dy;
}

static void	prepare_bresenham(t_fdf *fdf,
	t_point *start, t_point *end, t_bresenham *bres)
{
	*start = fdf_project(fdf, *start);
	*end = fdf_project(fdf, *end);
	init_bresenham(bres, *start, *end);
}

void	fdf_draw_line(t_fdf *fdf, t_point start, t_point end)
{
	t_bresenham	bres;

	prepare_bresenham(fdf, &start, &end, &bres);
	while (1)
	{
		put_pixel(fdf, start.x, start.y, start.color);
		if (start.x == end.x && start.y == end.y)
			break ;
		bres.e2 = 2 * bres.error;
		if (bres.e2 > bres.dy)
		{
			if (start.x == end.x)
				break ;
			bres.error += bres.dy;
			start.x += bres.sx;
		}
		if (bres.e2 <= bres.dx)
		{
			if (start.y == end.y)
				break ;
			bres.error += bres.dx;
			start.y += bres.sy;
		}
	}
}

void	fdf_draw_menu(t_fdf *fdf)
{
	int		y;
	int		color;
	void	*mlx;
	void	*win;

	color = FDF_WHITE;
	mlx = fdf->mlx_ptr;
	win = fdf->win_ptr;
	y = 0;
	mlx_string_put(mlx, win, 25, y += 50, color, "Controls");
	mlx_string_put(mlx, win, 25, y += 40, color, "Move: Arrows");
	mlx_string_put(mlx, win, 25, y += 30, color, "Zoom: +/- or Scroll");
	mlx_string_put(mlx, win, 25, y += 30, color, "Zoom Z-axis: PgUp/PgDown");
	mlx_string_put(mlx, win, 25, y += 30, color, "Rotate:");
	mlx_string_put(mlx, win, 35, y += 20, color, "x: A / D");
	mlx_string_put(mlx, win, 35, y += 20, color, "y: W / S");
	mlx_string_put(mlx, win, 35, y += 20, color, "z: Z / X");
	mlx_string_put(mlx, win, 25, y += 30, color, "Toggle Projection: P");
	mlx_string_put(mlx, win, 25, y += 30, color, "Toggle Monochrome: M");
	mlx_string_put(mlx, win, 25, y += 30, color, "Reset: R");
	mlx_string_put(mlx, win, 25, y += 30, color, "Exit: Esc");
}
