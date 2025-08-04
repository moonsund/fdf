#include "fdf.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 800

void center_projection(t_fdf *fdf);

bool init_window(t_map *map, t_fdf *fdf)
{    
    fdf->map = map; 
    fdf->zoom = 10;
    fdf->z_scale = 2;
    fdf->limits.max_zoom = 30;
    fdf->limits.min_zoom = 10;
    fdf->projection = ISO;
    center_projection(fdf);

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

void center_projection(t_fdf *fdf)
{
	int x, y;
	int screen_x, screen_y;
	int min_x = WIN_WIDTH;
	int min_y = WIN_HEIGHT;
	int max_x = 0;
	int max_y = 0;
	t_point p;

	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			p.x = x * fdf->zoom;
			p.y = y * fdf->zoom;
			p.z = fdf->map->height_map[y][x] * fdf->z_scale;

			if (fdf->projection == ISO)
				to_isometric(&p.x, &p.y, p.z);
			else
				to_paralel(&p.x, &p.y, p.z);

			screen_x = p.x;
			screen_y = p.y;

			if (screen_x < min_x) 
                min_x = screen_x;
			if (screen_x > max_x) 
                max_x = screen_x;
			if (screen_y < min_y) 
                min_y = screen_y;
			if (screen_y > max_y) 
                max_y = screen_y;
			x++;
		}
		y++;
	}

	int image_width = max_x - min_x;
	int image_height = max_y - min_y;

	fdf->shift_x = (WIN_WIDTH - image_width) / 2 - min_x;
	fdf->shift_y = (WIN_HEIGHT - image_height) / 2 - min_y;
}