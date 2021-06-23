#include "cub3d.h"

static void	calc_pln_inter(t_vect3 *inter, t_vect3 *dir, double t, t_data *data)
{
	inter->x = data->pos.x + dir->x * t;
	inter->y = data->pos.y + dir->y * t;
	inter->z = data->pos.z + dir->z * t;
}

static double	calc_pln_dist(t_vect3 *dir, t_pln *pln)
{
	return (pln->tnum
		/ (pln->n.x * dir->x + pln->n.y * dir->y + pln->n.z * dir->z));
}

static void	search_next_xwall(t_cast_info *info, t_vect3 *dir, t_data *data)
{
	info->yt = calc_pln_dist(dir, data->plns.ns + info->y_i);
	calc_pln_inter(&(info->inter), dir, info->yt, data);
	if (info->inter.z > 1.)
		info->yclr = data->clrs.c;
	else if (info->inter.z < 0.)
		info->yclr = data->clrs.f;
	else if (info->ydir == 1 && info->y_i < data->map_h
		&& info->inter.x >= 0. && info->inter.x < (double)data->map_w
		&& data->map[info->y_i][(int)floor(info->inter.x)] == '1')
		info->yclr = get_img_pixel(&(data->ttrs.so), \
floor((1 - info->inter.x + floor(info->inter.x)) \
	* (double)data->ttrs.so.w - 1e-10), \
floor((1 - info->inter.z + floor(info->inter.z)) \
	* (double)data->ttrs.so.h - 1e-10));
	else if (info->ydir == -1 && info->y_i > 0
		&& info->inter.x >= 0. && info->inter.x < (double)data->map_w
		&& data->map[info->y_i - 1][(int)floor(info->inter.x)] == '1')
		info->yclr = get_img_pixel(&(data->ttrs.no), \
floor((info->inter.x - floor(info->inter.x)) \
	* (double)data->ttrs.no.w), \
floor((1 - info->inter.z + floor(info->inter.z)) \
	* (double)data->ttrs.no.h - 1e-10));
	info->y_i += info->ydir;
}

static void	search_next_ywall(t_cast_info *info, t_vect3 *dir, t_data *data)
{
	info->xt = calc_pln_dist(dir, data->plns.we + info->x_i);
	calc_pln_inter(&(info->inter), dir, info->xt, data);
	if (info->inter.z > 1.)
		info->xclr = data->clrs.c;
	else if (info->inter.z < 0.)
		info->xclr = data->clrs.f;
	else if (info->xdir == 1 && info->x_i < data->map_w
		&& info->inter.y >= 0. && info->inter.y < (double)data->map_h
		&& data->map[(int)floor(info->inter.y)][info->x_i] == '1')
		info->xclr = get_img_pixel(&(data->ttrs.ea), \
floor((info->inter.y - floor(info->inter.y)) \
	* (double)data->ttrs.ea.w), \
floor((1 - info->inter.z + floor(info->inter.z)) \
	* (double)data->ttrs.ea.h - 1e-10));
	else if (info->xdir == -1 && info->x_i > 0
		&& info->inter.y >= 0. && info->inter.y < (double)data->map_h
		&& data->map[(int)floor(info->inter.y)][info->x_i - 1] == '1')
		info->xclr = get_img_pixel(&(data->ttrs.we), \
floor((1 - info->inter.y + floor(info->inter.y)) \
	* (double)data->ttrs.we.w - 1e-10), \
floor((1 - info->inter.z + floor(info->inter.z)) \
	* (double)data->ttrs.we.h - 1e-10));
	info->x_i += info->xdir;
}

unsigned int	cast_ray_from_pos(t_vect3 *dir, t_data *data)
{
	t_cast_info	info;

	init_cast_info(&info, dir, data);
	while ((info.y_i >= 0 && info.y_i < data->map_h + 1)
		|| (info.x_i >= 0 && info.x_i < data->map_w + 1))
	{
		if ((info.y_i >= 0 && info.y_i < data->map_h + 1 && info.yt <= info.xt)
			|| info.x_i < 0 || info.x_i >= data->map_w + 1)
			search_next_xwall(&info, dir, data);
		if (info.yclr < 0xFF000000 && info.yt <= info.xt)
			return (info.yclr);
		if (info.xclr < 0xFF000000 && info.yt >= info.xt)
			return (info.xclr);
		if ((info.x_i >= 0 && info.x_i < data->map_w + 1 && info.yt >= info.xt)
			|| info.y_i < 0 || info.y_i >= data->map_h + 1)
			search_next_ywall(&info, dir, data);
		if (info.xclr < 0xFF000000 && info.yt >= info.xt)
			return (info.xclr);
		if (info.yclr < 0xFF000000 && info.yt <= info.xt)
			return (info.yclr);
	}
	return (0xFFFFFF);
	if (dir->z >= 0.)
		return (data->clrs.c);
	return (data->clrs.f);
}
