#include "cub3d.h"

static int	get_minimap_clr(int x, int y, t_data *data)
{
	x = (int)floor((double)(x - data->mmap.x_b)
			/ (double)(data->mmap.x_e - data->mmap.x_b) *(double)data->map_w);
	y = (int)floor((double)(y - data->mmap.y_b)
			/ (double)(data->mmap.y_e - data->mmap.y_b) *(double)data->map_h);
	if (data->map[y][x] == '1')
		return (MMAP_CLR_WALL);
	return (MMAP_CLR_FLOOR);
}

static int	calc_minimap_img(t_data *data)
{
	int	x;
	int	y;

	data->mmap.img.ptr = mlx_new_image(data->mlx, data->w, data->h);
	if (format_img(&(data->mmap.img), data->w, data->h))
		return (print_err("failed to allocate minimap"));
	y = data->mmap.y_b;
	while (y < data->mmap.y_e)
	{
		x = data->mmap.x_b;
		while (x < data->mmap.x_e)
		{
			img_pixel_put(&(data->mmap.img), get_minimap_clr(x, y, data),
				x, y);
			x++;
		}
		y++;
	}
	return (0);
}

int	calc_minimap(t_data *data)
{
	double	size;
	double	map_size;

	size = (double)data->w;
	if (data->w > data->h)
		size = (double)data->h;
	map_size = (double)data->map_w;
	if (data->map_w > data->map_h)
		map_size = (double)data->map_h;
	data->mmap.x_b = (int)floor(size * (MMAP_MARGIN + MMAP_SIZE
				* 0.5 * (1 - map_size / (double)data->map_h)));
	data->mmap.x_e = data->mmap.x_b
		+ (int)floor(size * MMAP_SIZE * map_size / (double)data->map_h);
	data->mmap.y_b = (int)floor(size * (MMAP_MARGIN + MMAP_SIZE
				* 0.5 * (1 - map_size / (double)data->map_w)));
	data->mmap.y_e = data->mmap.y_b
		+ (int)floor(size * MMAP_SIZE * map_size / (double)data->map_w);
	data->mmap.plr_xsize = (double)(data->mmap.x_e - data->mmap.x_b)
		/ (double)data->map_w;
	data->mmap.plr_ysize = (double)(data->mmap.y_e - data->mmap.y_b)
		/ (double)data->map_h;
	return (calc_minimap_img(data));
}
