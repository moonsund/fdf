/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:22:24 by lorlov            #+#    #+#             */
/*   Updated: 2025/08/10 23:38:59 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void change_zoom(t_fdf *fdf, int step, bool *need_redraw)
{	
	t_fdf	tmp;
	int new_zoom;

	if (step > 0)
		new_zoom = fdf->zoom + 1;
	else
		new_zoom = fdf->zoom - 1;
	if (new_zoom < 1)
		return ;
	tmp = *fdf;
	tmp.zoom = new_zoom;
	if (!recenter_if_fits(&tmp))
			return ;
	fdf->zoom = new_zoom;
    fdf->shift_x = tmp.shift_x;
    fdf->shift_y = tmp.shift_y;
	*need_redraw = true;
}

void change_z_scale(t_fdf *fdf, int step, bool *need_redraw)
{
	t_fdf	tmp;
	int new_z_scale;

	if (step > 0)
		new_z_scale = fdf->z_scale + 1;
	else
		new_z_scale = fdf->z_scale - 1;
	if (new_z_scale < 1)
		return ;
	tmp = *fdf;
	tmp.z_scale = new_z_scale;
	if (!recenter_if_fits(&tmp))
			return ;
	fdf->z_scale = new_z_scale;
    fdf->shift_x = tmp.shift_x;
    fdf->shift_y = tmp.shift_y;
	*need_redraw = true;
}

void	switch_projection(t_fdf *fdf, bool *need_redraw)
{
	if (fdf->projection == ISO)
		fdf->projection = PARALLEL;
	else
		fdf->projection = ISO; 
	*need_redraw = true;
}
