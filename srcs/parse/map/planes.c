#include "cub3d.h"

static t_pln	*set_walls_pln(double x, double y, double z, int size)
{
	int		i;
	t_pln	*pln;

	pln = malloc(sizeof(*pln) * size);
	if (pln == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		set_vect3(&(pln[i].n), x, y, z);
		pln[i].d = (double)i;
		pln[i].tnum = 0.;
		i++;
	}
	return (pln);
}

int	parse_plns(t_data *data)
{
	data->plns.we = set_walls_pln(-1., 0., 0., data->map_w + 1);
	if (data->plns.we == NULL)
		return (print_err("failed to allocate planes"));
	data->plns.ns = set_walls_pln(0., -1., 0., data->map_h + 1);
	if (data->plns.ns == NULL)
		return (print_err("failed to allocate planes"));
	return (0);
}
