/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:17:20 by lorlov            #+#    #+#             */
/*   Updated: 2025/08/10 15:38:56 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <X11/keysym.h>

# include <stdio.h> // size_t
# include <unistd.h> // write() close()
# include <stdlib.h> // free()
# include <fcntl.h> // open()
# include <math.h>
# include <stdbool.h>

typedef struct s_cell
{
	int	height;
	int colour;
}	t_cell;


typedef struct s_map
{
	t_cell	**cells; 
	int	width;
	int	height;
}	t_map;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}	t_line;

typedef struct s_bbox {
	int min_x;
	int min_y;
	int max_x;
	int max_y;
}	tbbox;

typedef struct s_bres_step
{
	int	dx; 
	int	dy;
	int	sx;
	int	sy;
}	t_bres_step;

typedef enum e_proj_type
{
	ISO,
	PARALLEL
}	t_proj_type;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_lims
{
	int	max_zoom;
	int	min_zoom;
	int	min_z_scale;
	int	max_z_scale;
	int	min_x;
	int	min_y;
	int	max_x;
	int	max_y;
}	t_lims;

typedef struct s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		*map;
	int			zoom;
	int			scale;
	int			z_scale;
	t_proj_type	projection;
	t_img		image;
	int			shift_x;
	int			shift_y;
	t_lims		limits;
}	t_fdf;

bool	parse_map(const char *file_path, t_map *map);

// init
bool	init_window(t_map *map, t_fdf *fdf);
void	get_shifts(t_fdf *fdf);
void	apply_projection(int *x, int *y, int z, t_fdf *fdf);

// draw
void	draw_image(t_fdf *fdf);
void	put_pixel(t_fdf *fdf, int x, int y, unsigned int color);

// events
void	handle_events(t_fdf *fdf);

// keys
void	increase_zoom(t_fdf *fdf, bool *need_redraw);
void	decrease_zoom(t_fdf *fdf, bool *need_redraw);
void	increase_z_scale(t_fdf *fdf, bool *need_redraw);
void	decrease_z_scale(t_fdf *fdf, bool *need_redraw);
void	switch_projection(t_fdf *fdf, bool *need_redraw);

// utils
void	free_array(char **array);
void	free_map_cells(t_cell **cells, int height);
void	free_map(t_map *map);
void	cleanup(t_fdf *fdf);

#endif
