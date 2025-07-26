#include "fdf.h"


typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}				t_img;

typedef struct s_mlx_data
{
    void *mlx_ptr;
    void *win_ptr;
    t_img img;
} t_mlx_data; 

static int color_screen(t_mlx_data *data, int color)
{
	int bytes_per_pixel = data->img.bits_per_pixel / 8;
	int y = 0;

	while (y < 400)
	{
		int x = 0;
		while (x < 400)
		{
			char *pixel = data->img.img_pixels_ptr + (y * data->img.line_len + x * bytes_per_pixel);
			*(unsigned int *)pixel = color;
			x++;
		}
		y++;
	}
}

static int change_screen_color(int keycode, t_mlx_data *data)
{
    if (keycode == XK_r)
        color_screen(data, 0xff0000);
    else if (keycode == XK_g)
        color_screen(data, 0x00ff00);
    else if (keycode == XK_b)
        color_screen(data, 0x0000ff);
    else if (keycode == XK_Escape)
        exit(0);

    // mlx_clear_window(data->mlx_ptr, data->win_ptr);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 50, 50);
	return 0; 
}

void test_mlx(void)
{
    t_mlx_data data;

    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, 500, 500, "new window");

    data.img.img_ptr = mlx_new_image(data.mlx_ptr, 500, 500);    
    data.img.img_pixels_ptr = mlx_get_data_addr(data.img.img_ptr,
        &data.img.bits_per_pixel,
        &data.img.line_len,
        &data.img.endian);


    mlx_key_hook(data.win_ptr, change_screen_color, &data);
    mlx_loop(data.mlx_ptr);
}