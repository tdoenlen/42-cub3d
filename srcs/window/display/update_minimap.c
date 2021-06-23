#include "cub3d.h"

static void	update_minimap_plr_pos(t_data *data)
{
	data->mmap.x_max = (data->pos.x + 0.1)
		* data->mmap.plr_xsize + (double)data->mmap.x_b;
	data->mmap.x_min = (data->pos.x - 0.1)
		* data->mmap.plr_xsize + (double)data->mmap.x_b;
	data->mmap.y_max = (data->pos.y + 0.1)
		* data->mmap.plr_ysize + (double)data->mmap.y_b;
	data->mmap.y_min = (data->pos.y - 0.1)
		* data->mmap.plr_ysize + (double)data->mmap.y_b;
}

static void	put_scaled_plr_on_minimap(t_data *data)
{
	int	x;
	int	y;

	y = floor(data->mmap.y_min);
	while (y <= (int)ceil(data->mmap.y_max))
	{
		x = floor(data->mmap.x_min);
		while (x <= (int)ceil(data->mmap.x_max))
		{
			img_pixel_put(&(data->vs), MMAP_CLR_PLR, x * 2, y * 2);
			img_pixel_put(&(data->vs), MMAP_CLR_PLR, x * 2 + 1, y * 2);
			img_pixel_put(&(data->vs), MMAP_CLR_PLR, x * 2, y * 2 + 1);
			img_pixel_put(&(data->vs), MMAP_CLR_PLR, x * 2 + 1, y * 2 + 1);
			x++;
		}
		y++;
	}
}

static void	put_plr_on_minimap(t_data *data)
{
	int	x;
	int	y;

	y = floor(data->mmap.y_min);
	while (y <= (int)ceil(data->mmap.y_max))
	{
		x = floor(data->mmap.x_min);
		while (x <= (int)ceil(data->mmap.x_max))
		{
			img_pixel_put(&(data->vs), MMAP_CLR_PLR, x, y);
			x++;
		}
		y++;
	}
}

void	update_minimap(t_data *data)
{
	update_minimap_plr_pos(data);
	if (data->is_scaled)
		put_scaled_plr_on_minimap(data);
	else
		put_plr_on_minimap(data);
}
