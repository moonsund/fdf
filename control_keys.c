#include "fdf.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 800

void redraw(t_fdf *fdf)
{
    if (fdf->image.img_ptr)
        mlx_destroy_image(fdf->mlx_ptr, fdf->image.img_ptr);

    center_projection(fdf);
    fdf->image.img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    fdf->image.img_pixels_ptr = mlx_get_data_addr(fdf->image.img_ptr,
                                        &fdf->image.bits_per_pixel,
                                        &fdf->image.line_len,
                                        &fdf->image.endian);

    draw_image(fdf);
}

int update_view_settings(int keycode, t_fdf *fdf)
{
    int need_redraw = 0;

    if (keycode == XK_equal) 
    {
        int new_zoom = fdf->zoom + 2;
        if (new_zoom > fdf->limits.max_zoom) 
            new_zoom = fdf->limits.max_zoom;
        if (new_zoom != fdf->zoom) 
        {
            fdf->zoom = new_zoom;
            need_redraw = 1;  
        }
    }

    else if (keycode == XK_minus) 
    {
        int new_zoom = fdf->zoom - 2;
        if (new_zoom < fdf->limits.min_zoom) 
            new_zoom = fdf->limits.min_zoom;
        if (new_zoom != fdf->zoom) 
        {
            fdf->zoom = new_zoom;
            need_redraw = 1;  
        }
    }

    else if (keycode == XK_Escape)
        exit(0);





    if (need_redraw) 
        redraw(fdf);
    return (0);
}


int close_window_cross(void *param)
{
    mlx_destroy_window(((t_fdf *)param)->mlx_ptr, ((t_fdf *)param)->win_ptr);
    exit(0);
    return (0);
}


