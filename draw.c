/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:16:56 by lorlov            #+#    #+#             */
/*   Updated: 2025/08/10 15:11:57 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line_between(t_line line, t_fdf *fdf);
static void	project_point(t_point *p, t_fdf *fdf);
static void	bresenham(t_line l, t_fdf *fdf);
static void	bresenham_step(t_line *l, int *err, t_bres_step step);

void	draw_image(t_fdf *fdf)
{
	int	y;
	int	x;

	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (x < fdf->map->width - 1)
				draw_line_between((t_line){x, y, x + 1, y}, fdf);
			if (y < fdf->map->height - 1)
				draw_line_between((t_line){x, y, x, y + 1}, fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
		fdf->image.img_ptr, 0, 0);
}

static void	draw_line_between(t_line line, t_fdf *fdf)
{
	t_point	a;
	t_point	b;

	a.x = line.x0;
	a.y = line.y0;
	a.z = fdf->map->cells[line.y0][line.x0].height;
	b.x = line.x1;
	b.y = line.y1;
	b.z = fdf->map->cells[line.y1][line.x1].height;
	project_point(&a, fdf);
	project_point(&b, fdf);
	bresenham((t_line){a.x, a.y, b.x, b.y}, fdf);
}

static void	project_point(t_point *p, t_fdf *fdf)
{
	p->x *= fdf->zoom;
	p->y *= fdf->zoom;
	p->z *= fdf->z_scale;
	apply_projection(&p->x, &p->y, p->z, fdf);
	p->x += fdf->shift_x;
	p->y += fdf->shift_y;
}

static void	bresenham(t_line l, t_fdf *fdf)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;

	dx = abs(l.x1 - l.x0);
	dy = abs(l.y1 - l.y0);
	if (l.x0 < l.x1)
		sx = 1;
	else
		sx = -1;
	if (l.y0 < l.y1)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (l.x0 != l.x1 || l.y0 != l.y1)
	{
		put_pixel(fdf, l.x0, l.y0, 0xFFFFFF);
		bresenham_step(&l, &err, (t_bres_step){dx, dy, sx, sy});
	}
	put_pixel(fdf, l.x1, l.y1, 0xFFFFFF);
}

static void	bresenham_step(t_line *l, int *err, t_bres_step step)
{
	int	e2;

	e2 = 2 * (*err);
	if (e2 > -step.dy)
	{
		*err -= step.dy;
		l->x0 += step.sx;
	}
	if (e2 < step.dx)
	{
		*err += step.dx;
		l->y0 += step.sy;
	}
}
