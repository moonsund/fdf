/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:16:56 by lorlov            #+#    #+#             */
/*   Updated: 2025/08/10 15:11:46 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 800

void	put_pixel(t_fdf *fdf, int x, int y, unsigned int color)
{
	int		bpp;
	char	*p;

	bpp = fdf->image.bits_per_pixel / 8;
	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	p = fdf->image.img_pixels_ptr + (y * fdf->image.line_len + x * bpp);
	*(unsigned int *)p = color;
}
