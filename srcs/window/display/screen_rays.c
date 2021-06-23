#include "cub3d.h"

void	calc_screen_rays(t_data *data)
{
	int	i;
	int	i_max;

	i = 0;
	i_max = data->w * data->h;
	while (i < i_max)
	{
		i++;
	}
}

static void	calc_ratios(double *rx_ptr, double *ry_ptr, t_data *data)
{
	double	w;
	double	h;
	double	fov_x;
	double	fov_y;

	w = (double)data->w;
	h = (double)data->h;
	fov_x = FOV * M_PI_4 / 30.;
	fov_y = fov_x;
	if (h < w)
		fov_y = fov_y * h / w;
	else
		fov_x = fov_x * w / h;
	*rx_ptr = 2. * tan(fov_x * 0.5) / w;
	*ry_ptr = 2. * tan(fov_y * 0.5) / h;
}

int	calc_base_screen_rays(t_data *data)
{
	int		x;
	int		y;
	double	rx;
	double	ry;

	data->bsr = malloc(sizeof(*(data->bsr)) * data->w * data->h);
	data->sr = malloc(sizeof(*(data->sr)) * data->w * data->h);
	if (data->bsr == NULL || data->sr == NULL)
		return (print_err("screen rays allocation failed"));
	calc_ratios(&rx, &ry, data);
	y = 0;
	while (y < data->h)
	{
		x = 0;
		while (x < data->w)
		{
			set_vect3(data->bsr + y * data->w + x,
				((double)x + 0.5 - (double)data->w * 0.5) * rx,
				-1.,
				((double)data->h * 0.5 - (double)y + 0.5) * ry);
			x++;
		}
		y++;
	}
	return (0);
}
