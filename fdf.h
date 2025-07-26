#ifndef FDF_H
#define FDF_H

#include "libft/libft.h"
#include "minilibx/mlx.h"
#include <X11/keysym.h>

#include <stdio.h> // size_t
#include <unistd.h> // write() close()
#include <stdlib.h> // free()
#include <fcntl.h> // open()


typedef struct s_map
{
    int     **height_map; 
    int     width;       
    int     height;      
}   t_map;

void test_mlx(void);
t_map *parse_map(const char *file_path);


// utils
void free_array(char **array);
void free_map_height(int **height_map, int height);
void free_map(t_map *map);
void print_map_height(t_map *map); // to be deleted




#endif