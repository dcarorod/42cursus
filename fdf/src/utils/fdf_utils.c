/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:21:09 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/27 09:42:55 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	*fdf_perror_null(char *str)
{
	perror(str);
	return (NULL);
}

int	fdf_hex_to_int(const char *str)
{
	return ((int)ft_strtol(str, NULL, 16));
}

void	fdf_cleanup_mlx(t_fdf *fdf)
{
	if (fdf)
	{
		if (fdf->img.img_ptr)
			mlx_destroy_image(fdf->mlx_ptr, fdf->img.img_ptr);
		if (fdf->win_ptr)
			mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		if (fdf->mlx_ptr)
		{
			mlx_destroy_display(fdf->mlx_ptr);
			free(fdf->mlx_ptr);
		}
		if (fdf->map)
			fdf_free_map(fdf->map);
		free(fdf);
	}
}

int	fdf_message_exit(char *str, int exit_code)
{
	ft_putstr(str);
	return (exit_code);
}

int	fdf_close_window(t_fdf *fdf)
{
	fdf_cleanup_mlx(fdf);
	exit (0);
	return (0);
}
