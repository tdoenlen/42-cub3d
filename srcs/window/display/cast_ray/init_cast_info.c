#include "cub3d.h"

static void	set_dir_and_index(int *dir_ptr, int *i_ptr, double pos_coord,
	double dir_coord)
{
	*dir_ptr = 1;
	if (dir_coord < 0.)
		*dir_ptr = -1;
	*i_ptr = (int)floor(pos_coord);
	if (*dir_ptr == 1)
		(*i_ptr)++;
}

void	init_cast_info(t_cast_info *info, t_vect3 *dir, t_data *data)
{
	set_dir_and_index(&(info->xdir), &(info->x_i), data->pos.x, dir->x);
	set_dir_and_index(&(info->ydir), &(info->y_i), data->pos.y, dir->y);
	info->xt = 0.;
	info->yt = 0.;
	info->xclr = 0xFF000000;
	info->yclr = 0xFF000000;
}
