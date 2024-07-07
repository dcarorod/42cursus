/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:40:49 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/27 11:58:08 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void	handle_zoom(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_PLUS || keycode == MOUSE_SCROLL_UP)
	{
		if (fdf->zoom < FT_INT_MAX - FDF_ZOOM_SHIFT)
			fdf->zoom += FDF_ZOOM_SHIFT;
	}
	else if (keycode == KEY_MINUS || keycode == MOUSE_SCROLL_DOWN)
	{
		if (fdf->zoom > FDF_ZOOM_SHIFT)
			fdf->zoom -= FDF_ZOOM_SHIFT;
	}
}

static void	adjust_view(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_M)
		fdf->monochrome = !fdf->monochrome;
	else if (keycode == KEY_P)
	{
		if (fdf->projection == 0)
			fdf->projection = 1;
		else
			fdf->projection = 0;
	}
	else if (keycode == KEY_PAGE_UP)
	{
		if (fdf->z_zoom > FDF_ZOOM_SHIFT)
			fdf->z_zoom -= FDF_ZOOM_SHIFT;
	}
	else if (keycode == KEY_PAGE_DOWN)
	{
		if (fdf->z_zoom < FT_INT_MAX - FDF_ZOOM_SHIFT)
			fdf->z_zoom += FDF_ZOOM_SHIFT;
	}
	fdf_render(fdf);
}

static void	rotate_image(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_W)
		fdf->ry -= FDF_ROT_SHIFT;
	else if (keycode == KEY_S)
		fdf->ry += FDF_ROT_SHIFT;
	else if (keycode == KEY_A)
		fdf->rx -= FDF_ROT_SHIFT;
	else if (keycode == KEY_D)
		fdf->rx += FDF_ROT_SHIFT;
	else if (keycode == KEY_X)
		fdf->rz -= FDF_ROT_SHIFT;
	else if (keycode == KEY_Z)
		fdf->rz += FDF_ROT_SHIFT;
}

int	fdf_key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		fdf_close_window(fdf);
	else if (keycode == KEY_LEFT)
		fdf->x_offset -= FDF_SHIFT;
	else if (keycode == KEY_RIGHT)
		fdf->x_offset += FDF_SHIFT;
	else if (keycode == KEY_UP)
		fdf->y_offset -= FDF_SHIFT;
	else if (keycode == KEY_DOWN)
		fdf->y_offset += FDF_SHIFT;
	else if (keycode == KEY_A || keycode == KEY_D || keycode == KEY_W
		|| keycode == KEY_S || keycode == KEY_Z || keycode == KEY_X)
		rotate_image(keycode, fdf);
	else if (keycode == KEY_R)
		fdf_init_params(fdf);
	else if (keycode == KEY_P || keycode == KEY_M
		|| keycode == KEY_PAGE_UP || keycode == KEY_PAGE_DOWN)
		adjust_view(keycode, fdf);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		handle_zoom(keycode, fdf);
	return (0);
}

int	fdf_mouse_hook(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
		handle_zoom(button, fdf);
	return (0);
}
