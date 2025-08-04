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
    // print_map_height(map); // to be deleted
    
    if (!init_window(&map, &fdf))
        return (1);

    draw_image(&fdf);



    mlx_key_hook(fdf.win_ptr, update_view_settings, &fdf);

    mlx_loop(fdf.mlx_ptr);
    free_map(&map);
    return (0);
}