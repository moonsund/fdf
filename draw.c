#include "fdf.h"

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

	// if (fdf->projection == ISO)
	// 	to_isometric(&p->x, &p->y, p->z);

    to_isometric(&p->x, &p->y, p->z);
    // to_paralel(&p->x, &p->y, p->z);

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

static void draw_wireframe(t_fdf *fdf)
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
    mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->image.img_ptr, 50, 50);
}


// static int change_color(int keycode, t_mlx_data *fdf)
// {
//     if (keycode == XK_r)
//         colorize_image(fdf, 0xff0000);
//     else if (keycode == XK_g)
//         colorize_image(fdf, 0x00ff00);
//     else if (keycode == XK_b)
//         colorize_image(fdf, 0x0000ff);
//     else if (keycode == XK_Escape)
//         exit(0);

//     // mlx_clear_window(data->mlx_ptr, data->win_ptr);
//     mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img.img_ptr, 50, 50);
// 	return 0; 
// }

void draw_image(t_map *map)
{
    t_fdf *fdf;
    fdf = malloc(sizeof(t_fdf));
    if (!fdf)
        return; // или вывод ошибки
    int margin = 100;
    int zoom = 100;
    // int zoom = 800 / map->width;
    
    int win_width = map->width * zoom + margin * 2;
    int win_height = map->height * zoom + margin * 2;

    if (win_width > 1920) win_width = 1920;
    if (win_height > 1080) win_height = 1080;


    if (zoom > 30) zoom = 30;
    if (zoom < 2) zoom = 1;

    fdf->map = map;
    fdf->zoom = zoom;
    fdf->margin = margin;
    fdf->map->width = map->width;
    fdf->map->height = map->height;

    fdf->shift_y = 100;
    fdf->shift_x = 300;
    fdf->z_scale = 1;

    fdf->mlx_ptr = mlx_init();
    fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, win_width, win_height, "FdF");

    fdf->image.img_ptr = mlx_new_image(fdf->mlx_ptr, win_width, win_height);    
    fdf->image.img_pixels_ptr = mlx_get_data_addr(fdf->image.img_ptr,
        &fdf->image.bits_per_pixel,
        &fdf->image.line_len,
        &fdf->image.endian);

    draw_wireframe(fdf);

    // mlx_key_hook(fdf.win_ptr, change_color, &fdf);
    mlx_loop(fdf->mlx_ptr);
}