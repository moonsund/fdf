/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:18:58 by lorlov            #+#    #+#             */
/*   Updated: 2025/08/08 13:19:33 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 800

void		get_shifts(t_fdf *fdf);
static void	init_limits(t_fdf *fdf);
static void	update_limits_for_point(int x, int y, t_fdf *fdf);

bool	init_window(t_map *map, t_fdf *fdf)
{
	fdf->map = map; 
	fdf->zoom = 10;
	fdf->z_scale = 2;
	fdf->projection = ISO;
	get_shifts(fdf);
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		return (false);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!fdf->win_ptr)
		return (false);
	fdf->image.img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->image.img_ptr)
		return (false);
	fdf->image.img_pixels_ptr = mlx_get_data_addr(fdf->image.img_ptr,
			&fdf->image.bits_per_pixel,
			&fdf->image.line_len,
			&fdf->image.endian);
	return (true);
}

void	get_shifts(t_fdf *fdf)
{
	int		x;
	int		y;

	y = 0;
	init_limits(fdf);
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			update_limits_for_point(x, y, fdf);
			x++;
		}
		y++;
	}
	fdf->shift_x = (WIN_WIDTH - (fdf->limits.max_x - fdf->limits.min_x)) / 2 
		- fdf->limits.min_x;
	fdf->shift_y = (WIN_HEIGHT - (fdf->limits.max_y - fdf->limits.min_y)) / 2
		- fdf->limits.min_y;
}

static void	init_limits(t_fdf *fdf)
{
	fdf->limits.min_x = WIN_WIDTH;
	fdf->limits.min_y = WIN_HEIGHT;
	fdf->limits.max_x = 0;
	fdf->limits.max_y = 0;
	fdf->limits.min_z_scale = 1;
	fdf->limits.max_z_scale = 10;
	fdf->limits.min_zoom = 10;
	fdf->limits.max_zoom = 30;
}

void	apply_projection(int *x, int *y, int z, t_fdf *fdf)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	if (fdf->projection == ISO)
	{
		*x = (prev_x - prev_y) * cos(0.523599);
		*y = (prev_x + prev_y) * sin(0.523599) - z;
	}
	else
	{
		*x = prev_x;
		*y = prev_y - z;
	}
}

static void	update_limits_for_point(int x, int y, t_fdf *fdf)
{
	int		screen_x;
	int		screen_y;
	t_point	p;

	p.x = x * fdf->zoom;
	p.y = y * fdf->zoom;
	p.z = fdf->map->map_heights[y][x] * fdf->z_scale;
	apply_projection(&p.x, &p.y, p.z, fdf);
	screen_x = p.x;
	screen_y = p.y;
	if (screen_x < fdf->limits.min_x)
		fdf->limits.min_x = screen_x;
	if (screen_x > fdf->limits.max_x)
		fdf->limits.max_x = screen_x;
	if (screen_y < fdf->limits.min_y)
		fdf->limits.min_y = screen_y;
	if (screen_y > fdf->limits.max_y)
		fdf->limits.max_y = screen_y;
}
