/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:42:01 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/27 11:34:52 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int argc, char *argv[])
{
	t_map		*map;
	t_fdf		*fdf;
	const char	*filename;

	if (argc != 2)
		return (fdf_message_exit("Usage: ./fdf <map_file.fdf>\n", EXIT_FAILURE));
	filename = argv[1];
	map = fdf_get_map(filename);
	if (!map)
		return (fdf_message_exit("Failed to load the map\n", EXIT_FAILURE));
	fdf = fdf_init(map);
	if (!fdf)
	{
		fdf_free_map(map);
		return (fdf_message_exit(FDF_ERROR_MALLOC, EXIT_FAILURE));
	}
	ft_putstr("Rendering image...\n");
	fdf_render(fdf);
	mlx_key_hook(fdf->win_ptr, &fdf_key_hook, fdf);
	mlx_mouse_hook(fdf->win_ptr, &fdf_mouse_hook, fdf);
	mlx_hook(fdf->win_ptr, 17, 0, &fdf_close_window, fdf);
	mlx_loop_hook(fdf->mlx_ptr, &fdf_render, fdf);
	mlx_loop(fdf->mlx_ptr);
	fdf_cleanup_mlx(fdf);
	return (0);
}
