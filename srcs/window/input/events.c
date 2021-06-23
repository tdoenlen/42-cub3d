#include "cub3d.h"

int	quit(t_data *data)
{
	free_data(data);
	exit(0);
	return (0);
}

int	key_pressed(int key, t_data *data)
{
	if (key == KEY_ESC
		|| (!lset_has_val(data->pk, KEY_CMD)
			&& lset_add(&(data->pk), key) == -1))
		quit(data);
	if (key == KEY_M)
	{
		data->is_m = 1;
		mlx_mouse_hide();
		mlx_mouse_move(data->win, data->w / 2, data->h / 2);
		mlx_mouse_get_pos(data->win, &(data->m_x), &(data->m_y));
	}
	return (0);
}

int	key_released(int key, t_data *data)
{
	lset_rm(&(data->pk), key);
	return (0);
}
