#include "fdf.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 800

static int handle_keys(int keycode, t_fdf *fdf);
static int handle_close(t_fdf *fdf);
static void redraw(t_fdf *fdf);

void handle_events(t_fdf *fdf)
{
    mlx_hook(fdf->win_ptr, 17, 0, handle_close, fdf); // крестик
    mlx_key_hook(fdf->win_ptr, handle_keys, fdf);      // клавиши
}

static int handle_keys(int keycode, t_fdf *fdf)
{
    bool need_redraw = false;

    if (keycode == XK_equal) 
        increase_zoom(fdf, &need_redraw);
    else if (keycode == XK_minus) 
        decrease_zoom(fdf, &need_redraw);

    else if (keycode == XK_0) 
        increase_z_scale(fdf, &need_redraw);
    else if (keycode == XK_9) 
        decrease_z_scale(fdf, &need_redraw);

    else if (keycode == XK_Escape)
        handle_close(fdf);
    
    else if (keycode == XK_s) 
        switch_projection(fdf, &need_redraw);

    if (need_redraw) 
        redraw(fdf);
    return (0);
}

static int handle_close(t_fdf *fdf)
{
    cleanup(fdf);
    exit(0);
}

static void redraw(t_fdf *fdf)
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