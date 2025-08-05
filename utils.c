#include "fdf.h"

void free_array(char **array)
{
    int i;

    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

void free_map_height(int **height_map, int height)
{
	int i;

	i = 0;
	while (i < height)
	{
		free(height_map[i]);
		i++;
	}
	free(height_map);
}

void free_map(t_map *map)
{
    if (!map)
        return;
    free_map_height(map->height_map, map->height);
    free(map);
}

void cleanup(t_fdf *fdf)
{
	if (fdf->image.img_ptr)
        mlx_destroy_image(fdf->mlx_ptr, fdf->image.img_ptr);
    if (fdf->win_ptr)
        mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
    mlx_destroy_display(fdf->mlx_ptr);
    if (fdf->mlx_ptr)
        free(fdf->mlx_ptr);
}