/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:18:58 by lorlov            #+#    #+#             */
/*   Updated: 2025/08/10 23:23:42 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 800

bool recenter_if_fits(t_fdf *fdf);
void	apply_projection(int *x, int *y, int z, t_fdf *fdf);
static void compute_box(t_fdf *fdf, t_bbox *box);
static void update_box(t_bbox *box, int sx, int sy);

bool	init_window(t_map *map, t_fdf *fdf)
{
	fdf->map = map; 
	fdf->zoom = 1;
	fdf->z_scale = 1;
	fdf->shift_x = 0;
	fdf->shift_y = 0;
	fdf->projection = ISO;
	recenter_if_fits(fdf);
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

bool recenter_if_fits(t_fdf *fdf)
{
    t_bbox box;
    int    w;
    int    h;

    compute_box(fdf, &box);
    w = box.max_x - box.min_x + 1;
    h = box.max_y - box.min_y + 1;
    if (w > WIN_WIDTH || h > WIN_HEIGHT)
        return (false);
    fdf->shift_x = (WIN_WIDTH  - w) / 2 - box.min_x;
    fdf->shift_y = (WIN_HEIGHT - h) / 2 - box.min_y;
    return true;
}

static void compute_box(t_fdf *fdf, t_bbox *box)
{
	int x;
    int y;
	t_point p;

	box->min_x = WIN_WIDTH;
    box->min_y = WIN_HEIGHT;
	box->max_x = 0;
    box->max_y = 0;
	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			p.x = x * fdf->zoom;
			p.y = y * fdf->zoom;
			p.z = fdf->map->cells[y][x].height * fdf->z_scale;
			apply_projection(&p.x, &p.y, p.z, fdf);
			update_box(box, p.x, p.y);
			x++;
		}
		y++;
	}
}

static void update_box(t_bbox *box, int sx, int sy)
{
	if (sx < box->min_x)
        box->min_x = sx;
	if (sx > box->max_x)
        box->max_x = sx;
	if (sy < box->min_y)
        box->min_y = sy;
	if (sy > box->max_y)
        box->max_y = sy;
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