#include "fdf.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 800

static void compute_box(t_fdf *fdf, t_bbox *box);
static void update_box(t_bbox *box, int sx, int sy);

bool fits_and_centered(t_fdf *fdf, int *out_sx, int *out_sy)
{
	t_bbox box;
	int w;
    int h;

	compute_box(fdf, &box);
	w = box.max_x - box.min_x;
	h = box.max_y - box.min_y;
	if (w > WIN_WIDTH || h > WIN_HEIGHT)
		return (false);
	*out_sx = (WIN_WIDTH  - w) / 2 - box.min_x;
	*out_sy = (WIN_HEIGHT - h) / 2 - box.min_y;
	return (true);
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

// static void box_init(t_bbox *box)
// {
// 	box->min_x = WIN_WIDTH;
//     box->min_y = WIN_HEIGHT;
// 	box->max_x = 0;
//     box->max_y = 0;
// }