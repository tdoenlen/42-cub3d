#include "cub3d.h"

static void	check_line_not_in_map(t_data *data)
{
	int	i;

	if (data->map)
	{
		i = 0;
		while (data->map[i] && data->map[i] != data->prs.line)
			i++;
		if (data->map[i] == data->prs.line)
			data->prs.line = NULL;
	}
}

void	free_data(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->vs.ptr)
		mlx_destroy_image(data->mlx, data->vs.ptr);
	check_line_not_in_map(data);
	data->map = safe_free_str_tab(data->map);
	data->bsr = safe_free(data->bsr);
	data->sr = safe_free(data->sr);
	lset_clear(&(data->pk));
	if (data->ttrs.no.ptr)
		mlx_destroy_image(data->mlx, data->ttrs.no.ptr);
	if (data->ttrs.so.ptr)
		mlx_destroy_image(data->mlx, data->ttrs.so.ptr);
	if (data->ttrs.we.ptr)
		mlx_destroy_image(data->mlx, data->ttrs.we.ptr);
	if (data->ttrs.ea.ptr)
		mlx_destroy_image(data->mlx, data->ttrs.ea.ptr);
	if (data->ttrs.s.ptr)
		mlx_destroy_image(data->mlx, data->ttrs.s.ptr);
	data->plns.we = safe_free(data->plns.we);
	data->plns.ns = safe_free(data->plns.ns);
	data->prs.line = safe_free(data->prs.line);
	if (data->prs.fd != -1)
		close(data->prs.fd);
}
