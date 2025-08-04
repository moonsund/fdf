#include "fdf.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 800


void bresenham(int x0, int y0, int x1, int y1, t_fdf *fdf)
{
	int	dx = abs(x1 - x0);
	int	dy = abs(y1 - y0);
	int	sx = (x0 < x1) ? 1 : -1;
	int	sy = (y0 < y1) ? 1 : -1;
	int	err = dx - dy;
    int bytes_per_pixel = fdf->image.bits_per_pixel / 8;

	while (x0 != x1 || y0 != y1)
	{
        char *pixel = fdf->image.img_pixels_ptr + (y0 * fdf->image.line_len + x0 * bytes_per_pixel);
        *(unsigned int *)pixel = 0xFFFFFF; // белый

		int	e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	to_isometric(int *x, int *y, int z)
{
	int	prev_x = *x;
	int	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);    // 30°
	*y = (prev_x + prev_y) * sin(0.523599) - z;
}

void to_paralel(int *x, int *y, int z)
{
    int	prev_x = *x;
	int	prev_y = *y;

    *x = prev_x;
    *y = prev_y - z;
}

void	project_point(t_point *p, t_fdf *fdf)
{
	p->x *= fdf->zoom;
	p->y *= fdf->zoom;
	p->z *= fdf->z_scale;

	if (fdf->projection == ISO)
        to_isometric(&p->x, &p->y, p->z);
    else
        to_paralel(&p->x, &p->y, p->z);


	p->x += fdf->shift_x;
	p->y += fdf->shift_y;
}

void	draw_line_between(int x0, int y0, int x1, int y1, t_fdf *fdf)
{
	t_point	a;
	t_point	b;

	a.x = x0;
	a.y = y0;
	a.z = fdf->map->height_map[y0][x0];

	b.x = x1;
	b.y = y1;
	b.z = fdf->map->height_map[y1][x1];

	project_point(&a, fdf);
	project_point(&b, fdf);

	bresenham(a.x, a.y, b.x, b.y, fdf);
}

void draw_image(t_fdf *fdf)
{
    int y;
    int x;

    y = 0;
    while (y < fdf->map->height)
    {
        x = 0;
        while (x < fdf->map->width)
        {
            if (x < fdf->map->width - 1)
                draw_line_between(x, y, x + 1, y, fdf);
            if (y < fdf->map->height - 1)
                draw_line_between(x, y, x, y + 1, fdf);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->image.img_ptr, 0, 0);
}