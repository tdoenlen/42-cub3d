#include "cub3d.h"

static void	init_img(t_img *img)
{
	img->ptr = NULL;
	img->addr = NULL;
	img->w = 0;
	img->h = 0;
	img->l = 0;
	img->p = 0;
	img->e = 0;
}

static void	init_ttrs(t_ttrs *ttrs)
{
	init_img(&(ttrs->no));
	init_img(&(ttrs->so));
	init_img(&(ttrs->we));
	init_img(&(ttrs->ea));
	init_img(&(ttrs->s));
}

static void	init_prs(char *file, t_prs *prs)
{
	prs->file = file;
	prs->fd = -1;
	prs->line = NULL;
	prs->line_num = 0;
}

static void	init_rem_parts_of_data(t_data *data)
{
	data->plns.we = NULL;
	data->plns.ns = NULL;
	data->m_x = 0;
	data->m_y = 0;
	data->is_m = 0;
	data->selems = 0;
}

int	init_data(char *file, t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (print_err("failed to initialize minilibX"));
	data->win = NULL;
	init_img(&(data->vs));
	data->is_scaled = 0;
	data->bsr = NULL;
	data->sr = NULL;
	set_vect3(&(data->pos), -1., -1., SIZE);
	data->xa = 0.;
	data->ya = 0.;
	data->za = 0.;
	data->w = 0;
	data->h = 0;
	data->map = NULL;
	data->map_w = 0;
	data->map_h = 0;
	data->pk = NULL;
	data->clrs.f = 0;
	data->clrs.c = 0;
	init_ttrs(&(data->ttrs));
	init_prs(file, &(data->prs));
	init_rem_parts_of_data(data);
	return (0);
}
