#include "cub3d.h"

static void	update_delta(t_data *data)
{
	static struct timeval	last_time = {0, 0};
	struct timeval			time;

	gettimeofday(&time, NULL);
	if (last_time.tv_sec == 0)
		time.tv_usec = 0;
	data->delta = ((double)time.tv_usec - (double)last_time.tv_usec) / 1e6;
	if (data->delta < 0.)
		data->delta = 0.;
	last_time = time;
}

static void	update_plns(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_w + 1)
	{
		data->plns.we[i].tnum = -data->plns.we[i].n.x * data->pos.x
			- data->plns.we[i].n.y * data->pos.y
			- data->plns.we[i].n.z * data->pos.z
			- data->plns.we[i].d;
		i++;
	}
	i = 0;
	while (i < data->map_h + 1)
	{
		data->plns.ns[i].tnum = -data->plns.ns[i].n.x * data->pos.x
			- data->plns.ns[i].n.y * data->pos.y
			- data->plns.ns[i].n.z * data->pos.z
			- data->plns.ns[i].d;
		i++;
	}
}

static void	update_fps_counter(void)
{
	static int			frame = 0;
	static time_t		old_time = 0;
	time_t				cur_time;

	time(&cur_time);
	if (difftime(old_time, cur_time) && frame)
	{
		printf("frames: %d\n", frame);
		frame = 0;
	}
	frame++;
	old_time = cur_time;
}

static void	update_mouse_rot(t_data *data)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(data->win, &x, &y);
	data->za += RSPEED * M_PI_4 / 30 * 0.001 * (double)(x - data->m_x);
	data->xa += RSPEED * M_PI_4 / 30 * 0.001 * (double)(y - data->m_y);
	if (data->xa > M_PI_2)
		data->xa = M_PI_2;
	if (data->xa < -M_PI_2)
		data->xa = -M_PI_2;
	mlx_mouse_move(data->win, data->w / 2, data->h / 2);
}

int	update(t_data *data)
{
	update_delta(data);
	if (data->is_m)
		update_mouse_rot(data);
	check_pressed_keys(data);
	update_plns(data);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, data->win);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, data->vs.ptr);
	get_vect3_rotate_z(data->bsr, cos(data->za), sin(data->za));
	get_vect3_rotate_x(data->bsr, cos(data->xa), sin(data->xa));
	update_vs(data);
	mlx_put_image_to_window(data->mlx, data->win, data->vs.ptr, 0, 0);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, data->win);
	update_fps_counter();
	return (0);
}
