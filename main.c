#include "fdf.h"

int main(int argc, char **argv)
{
    t_map *map;

    if (argc != 2)
    {
        ft_putstr_fd("Usage: ./fdf <map_file>\n", 2);
        return (1);
    }
    map = parse_map(argv[1]);
    if (!map)
    {
        return (1);
    }
    print_map_height(map);
    
    draw_image(map);
    free_map(map);


    return (0);
}