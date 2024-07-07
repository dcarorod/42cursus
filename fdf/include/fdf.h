/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaro-ro <dcaro-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:52:01 by dcaro-ro          #+#    #+#             */
/*   Updated: 2024/06/27 15:47:10 by dcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "../lib/libft/include/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include "fdf_color.h"
# include "fdf_keycodes.h"

# ifndef FDF_BUFFER_SIZE
#  define FDF_BUFFER_SIZE 1024
# endif

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define FDF_30G_RAD 0.523599
# define FDF_ZOOM_SHIFT 0.5
# define FDF_ROT_SHIFT 0.1
# define FDF_SHIFT 5

# define FDF_ERROR_MALLOC "Error: Memory allocation failed\n"
# define FDF_ERROR_EXTENSION "Error: Invalid file extension\n"
# define FDF_ERROR_OPEN "Error opening file\n"
# define FDF_ERROR_WIDTH "Error: Inconsistent number of elements in map line\n"

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
	int	e2;
}	t_bresenham;

typedef struct s_map
{
	int	width;
	int	height;
	int	**z_mt;
	int	min_z;
	int	max_z;
	int	**colors;
	int	iscolor;
}	t_map;

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_image;

/* projection: 0 for isometric
	rx, ry, rz: rotations
 */
typedef struct s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	*map;
	t_image	img;
	float	zoom;
	float	z_zoom;
	float	x_offset;
	float	y_offset;
	float	rx;
	float	ry;
	float	rz;
	int		projection;
	int		monochrome;
}	t_fdf;

/* Map parsing*/

int		**allocate_matrix(int width, int height);
int		is_valid_element(const char *str);
int		validate_elements(const char *line);
t_map	*fdf_initialize_map(int width, int height);
t_map	*fdf_fill_map(char **lines, int height, int width);
int		fdf_count_line_elements(const char *line);
int		fdf_read_lines(int fd, char ***lines, int *width, int *flag);
t_map	*fdf_get_map(const char *filename);

/* Utils */

void	*fdf_free_and_null(void *ptr);
void	fdf_free_matrix(int **matrix, int height);
void	fdf_free_map(t_map *map);
void	*fdf_cleanup(t_map *map, char **split);
void	*fdf_cleanup_null(void *ptr, void (*free_function)(void *));
void	*fdf_perror_null(char *str);
int		fdf_hex_to_int(const char *str);
int		fdf_message_exit(char *str, int exit_code);

/* MLX */

void	fdf_init_params(t_fdf *fdf);
t_fdf	*fdf_init(t_map *map);

/* Drawing */
t_point	fdf_project(t_fdf *fdf, t_point point);
void	fdf_draw_line(t_fdf *fdf, t_point start, t_point end);
void	fdf_draw_menu(t_fdf *fdf);
void	fdf_draw_map(t_fdf *fdf);
int		fdf_render(t_fdf *fdf);

/* Hooks */
int		fdf_close_window(t_fdf *fdf);
int		fdf_key_hook(int keycode, t_fdf *fdf);
int		fdf_mouse_hook(int button, int x, int y, t_fdf *fdf);

/* MLX Utils */
void	fdf_cleanup_mlx(t_fdf *fdf);

#endif
