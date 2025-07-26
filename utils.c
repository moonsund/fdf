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


void print_map_height(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{	
			printf("%i ", map->height_map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}