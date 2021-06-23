#include "cub3d.h"

static int	get_vs_pixel(int x, int y, t_data *data)
{
	int	i;

	if (x >= data->mmap.x_b && x < data->mmap.x_e && y >= data->mmap.y_b
		&& y < data->mmap.y_e)
		return (get_img_pixel(&(data->mmap.img), x, y));
	i = y * data->w + x;
	data->sr[i] = get_vect3_rotate_x(data->bsr + i, NAN, NAN);
	data->sr[i] = get_vect3_rotate_z(data->sr + i, NAN, NAN);
	return (cast_ray_from_pos(data->sr + i, data));
}

static void	*thread_update_pixels(void *arg)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	static int				n = 0;
	t_data					*data;
	int						i;
	int						i_max;

	pthread_mutex_lock(&mutex);
	if (n == 4)
		n = 0;
	data = (t_data *)arg;
	i = n;
	n++;
	pthread_mutex_unlock(&mutex);
	i_max = data->w * data->h;
	while (i < i_max)
	{
		img_addr_pixel_put(&(data->vs),
			get_vs_pixel(i % data->w, i / data->w, data), i);
		i += 4;
	}
	return (NULL);
}

static void	update_scaled_pixels(int y, t_data *data)
{
	int		x;
	int		clr;

	while (y < data->h)
	{
		x = 0;
		while (x < data->w)
		{
			clr = get_vs_pixel(x, y, data);
			img_pixel_put(&(data->vs), clr, x * 2, y * 2);
			img_pixel_put(&(data->vs), clr, x * 2 + 1, y * 2);
			img_pixel_put(&(data->vs), clr, x * 2, y * 2 + 1);
			img_pixel_put(&(data->vs), clr, x * 2 + 1, y * 2 + 1);
			x++;
		}
		y += 4;
	}
}

static void	*thread_update_scaled_pixels(void *arg)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	static int				n = 0;
	int						y;

	pthread_mutex_lock(&mutex);
	if (n == 4)
		n = 0;
	y = n;
	n++;
	pthread_mutex_unlock(&mutex);
	update_scaled_pixels(y, (t_data *)arg);
	return (NULL);
}

void	update_vs(t_data *data)
{
	pthread_t	th_ids[4];
	void		*(*th_func)(void *);
	int			th_i;

	if (data->is_scaled)
		th_func = thread_update_scaled_pixels;
	else
		th_func = thread_update_pixels;
	th_i = 0;
	while (th_i < 4)
	{
		pthread_create(th_ids + th_i, NULL, th_func, data);
		th_i++;
	}
	th_i = 0;
	while (th_i < 4)
	{
		pthread_join(th_ids[th_i], NULL);
		th_i++;
	}
	update_minimap(data);
}
