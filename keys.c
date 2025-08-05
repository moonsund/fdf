#include "fdf.h"

void increase_zoom(t_fdf *fdf, bool *need_redraw)
{
    int new_zoom = fdf->zoom + 2;
    if (new_zoom > fdf->limits.max_zoom) 
        new_zoom = fdf->limits.max_zoom;
    if (new_zoom != fdf->zoom) 
    {
        fdf->zoom = new_zoom;
        *need_redraw = true;  
    }
}

void decrease_zoom(t_fdf *fdf, bool *need_redraw)
{
    int new_zoom = fdf->zoom - 2;
    if (new_zoom < fdf->limits.min_zoom) 
            new_zoom = fdf->limits.min_zoom;
    if (new_zoom != fdf->zoom) 
    {
        fdf->zoom = new_zoom;
        *need_redraw = true;  
    }
}

void increase_z_scale(t_fdf *fdf, bool *need_redraw)
{
    int new_z_scale = fdf->z_scale + 1;
    if (new_z_scale > fdf->limits.max_z_scale) 
        new_z_scale = fdf->limits.max_z_scale;
    if (new_z_scale != fdf->z_scale) 
    {
        fdf->z_scale = new_z_scale;
        *need_redraw = true;  
    }
}

void decrease_z_scale(t_fdf *fdf, bool *need_redraw)
{
    int new_z_scale = fdf->z_scale - 1;
    if (new_z_scale < fdf->limits.min_z_scale) 
        new_z_scale = fdf->limits.min_z_scale;
    if (new_z_scale != fdf->z_scale) 
    {
        fdf->z_scale = new_z_scale;
        *need_redraw = true;  
    }
}

void switch_projection(t_fdf *fdf, bool *need_redraw)
{
    if (fdf->projection == ISO) 
        fdf->projection = PARALLEL;
    else
        fdf->projection = ISO; 
    *need_redraw = true;  
}