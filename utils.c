/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:33:46 by lorlov            #+#    #+#             */
/*   Updated: 2025/08/06 17:42:29 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_map_heights(int **map_heights, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map_heights[i]);
		i++;
	}
	free(map_heights);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	free_map_heights(map->map_heights, map->height);
	free(map);
}

void	cleanup(t_fdf *fdf)
{
	if (fdf->image.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->image.img_ptr);
	if (fdf->win_ptr)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	mlx_destroy_display(fdf->mlx_ptr);
	if (fdf->mlx_ptr)
		free(fdf->mlx_ptr);
}
