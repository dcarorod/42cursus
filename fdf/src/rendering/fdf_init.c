/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:31:48 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/27 11:32:34 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* Initialize and create window */
static void	fdf_init_mlx(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		fdf_perror_null("Failed to initialize MiniLibX");
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!fdf->win_ptr)
		fdf_perror_null("Failed to create window");
}

static void	fdf_init_image(t_fdf *fdf)
{
	fdf->img.img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img.img_ptr)
		fdf_perror_null("Failed to create image");
	fdf->img.addr = mlx_get_data_addr(fdf->img.img_ptr,
			&fdf->img.bpp, &fdf->img.size_line, &fdf->img.endian);
	if (!fdf->img.addr)
		fdf_perror_null("Failed to get image data");
}

void	fdf_init_params(t_fdf *fdf)
{
	fdf->zoom = ft_max((WIN_WIDTH / fdf->map->width / 2.0),
			(WIN_HEIGHT / fdf->map->height / 2.0));
	fdf->z_zoom = 2.0;
	fdf->x_offset = WIN_WIDTH / 2.0;
	fdf->y_offset = (WIN_HEIGHT - fdf->map->height * fdf->zoom) / 2.0;
	fdf->rx = 0.0;
	fdf->ry = 0.0;
	fdf->rz = 0.0;
	fdf->projection = 0;
	fdf->monochrome = FALSE;
}

t_fdf	*fdf_init(t_map *map)
{
	t_fdf	*fdf;

	if (!map)
		return (NULL);
	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
	{
		fdf_free_map(map);
		return (fdf_perror_null("Failed to allocate memory for FdF structure"));
	}
	fdf_init_mlx(fdf);
	fdf_init_image(fdf);
	fdf->map = map;
	fdf_init_params(fdf);
	if (!fdf->mlx_ptr || !fdf->win_ptr || !fdf->img.img_ptr || !fdf->img.addr)
	{
		fdf_cleanup_mlx(fdf);
		return (NULL);
	}
	return (fdf);
}
