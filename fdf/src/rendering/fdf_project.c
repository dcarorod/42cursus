/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:02:50 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/27 11:33:02 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void	fdf_rotate(t_fdf *fdf, int *x, int *y, int *z)
{
	int	previous_x;
	int	previous_y;
	int	previous_z;

	previous_y = *y;
	previous_z = *z;
	*y = previous_y * cos(fdf->rx) - previous_z * sin(fdf->rx);
	*z = previous_y * sin(fdf->rx) + previous_z * cos(fdf->rx);
	previous_x = *x;
	previous_z = *z;
	*x = previous_x * cos(fdf->ry) + previous_z * sin(fdf->ry);
	*z = previous_z * cos(fdf->ry) - previous_x * sin(fdf->ry);
	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(fdf->rz) - previous_y * sin(fdf->rz);
	*y = previous_x * sin(fdf->rz) + previous_y * cos(fdf->rz);
}

static void	fdf_project_iso(t_fdf *fdf, int *x, int *y, int z)
{
	int	previous_x;
	int	previous_y;

	if (!fdf || fdf->projection != 0)
		return ;
	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(FDF_30G_RAD);
	*y = (previous_x + previous_y) * sin(FDF_30G_RAD) - z;
}

t_point	fdf_project(t_fdf *fdf, t_point point)
{
	point.x *= fdf->zoom;
	point.y *= fdf->zoom;
	point.z *= fdf->zoom / fdf->z_zoom;
	fdf_rotate(fdf, &point.x, &point.y, &point.z);
	if (fdf->projection == 0)
		fdf_project_iso(fdf, &point.x, &point.y, point.z);
	point.x += fdf->x_offset;
	point.y += fdf->y_offset;
	return (point);
}
