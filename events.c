/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:17:05 by lorlov            #+#    #+#             */
/*   Updated: 2025/08/10 23:45:43 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 800

static int	handle_keys(int keycode, t_fdf *fdf);
static int	handle_close(t_fdf *fdf);
static void	redraw(t_fdf *fdf);

void	handle_events(t_fdf *fdf)
{
	mlx_hook(fdf->win_ptr, 17, 0, handle_close, fdf);
	mlx_key_hook(fdf->win_ptr, handle_keys, fdf);
}

static int	handle_keys(int keycode, t_fdf *fdf)
{
	bool	need_redraw;

	need_redraw = false;
	if (keycode == XK_equal)
		change_zoom(fdf, +1, &need_redraw);
	else if (keycode == XK_minus)
		change_zoom(fdf, -1, &need_redraw);
	else if (keycode == XK_0)
		change_z_scale(fdf, +1, &need_redraw);
	else if (keycode == XK_9)
		change_z_scale(fdf, -1, &need_redraw);
	else if (keycode == XK_Escape)
		handle_close(fdf);
	else if (keycode == XK_s)
		switch_projection(fdf, &need_redraw);
	if (need_redraw)
		redraw(fdf);
	return (0);
}

static int	handle_close(t_fdf *fdf)
{
	cleanup(fdf);
	exit(0);
}

static void	redraw(t_fdf *fdf)
{
	if (fdf->image.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->image.img_ptr);
	recenter_if_fits(fdf);
	fdf->image.img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	fdf->image.img_pixels_ptr = mlx_get_data_addr(fdf->image.img_ptr, 
			&fdf->image.bits_per_pixel,
			&fdf->image.line_len,
			&fdf->image.endian);
	draw_image(fdf);
}
