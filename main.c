#include "fdf.h"

int main(int argc, char **argv)
{
    t_map map;
    t_fdf fdf;

    if (argc != 2)
    {
        ft_putstr_fd("Usage: ./fdf <map_file>\n", 2);
        return (1);
    }
    if (!parse_map(argv[1], &map))
        return (1);
    if (!init_window(&map, &fdf))
        return (1);
    draw_image(&fdf);
    handle_events(&fdf);
    mlx_loop(fdf.mlx_ptr);
    free_map(&map);
    cleanup(&fdf);
    return (0);
}