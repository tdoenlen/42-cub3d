#include "cub3d.h"

static void	remove_ttr_transparency(t_img *ttr)
{
	int	x;
	int	y;

	y = 0;
	while (y < ttr->h)
	{
		x = 0;
		while (x < ttr->w)
		{
			if ((unsigned int)get_img_pixel(ttr, x, y) > 0xFFFFFF)
				img_pixel_put(ttr, 0xFFFFFF, x, y);
			x++;
		}
		y++;
	}
}

static void	remove_wall_ttrs_transparency(t_data *data)
{
	remove_ttr_transparency(&(data->ttrs.ea));
	remove_ttr_transparency(&(data->ttrs.no));
	remove_ttr_transparency(&(data->ttrs.so));
	remove_ttr_transparency(&(data->ttrs.we));
}

int	parse_file(t_data *data)
{
	if (parse_elems(data))
		return (-1);
	remove_wall_ttrs_transparency(data);
	printf("Begin map parsing at line %d.\n", data->prs.line_num);
	if (parse_map(data))
		return (-1);
	printf("Nice! No error occured while parsing file!\n");
	close(data->prs.fd);
	return (0);
}
