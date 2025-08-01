#ifndef FDF_H
#define FDF_H

#include "libft/libft.h"
#include "minilibx/mlx.h"
#include <X11/keysym.h>

#include <stdio.h> // size_t
#include <unistd.h> // write() close()
#include <stdlib.h> // free()
#include <fcntl.h> // open()
#include <math.h>


typedef struct s_map
{
    int     **height_map; 
    int     width;       
    int     height;      
}   t_map;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

typedef enum e_proj_type
{
	ISO,
	PARALLEL
}	t_proj_type;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
} t_img;

typedef struct s_fdf
{
    void *mlx_ptr;
    void *win_ptr;
    t_map *map;
    int zoom;
    int scale;
    int margin;
    t_proj_type projection;
    t_img image;
    int shift_x;
    int shift_y;
    int z_scale;
} t_fdf;


t_map *parse_map(const char *file_path);
void draw_image(t_map *map); 


// utils
void free_array(char **array);
void free_map_height(int **height_map, int height);
void free_map(t_map *map);
void print_map_height(t_map *map); // to be deleted




#endif