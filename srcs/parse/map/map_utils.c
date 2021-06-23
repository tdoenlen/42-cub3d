#include "cub3d.h"

static void	map_replace_space_with_wall(t_data *data)
{
	int	l;
	int	c;

	l = 0;
	while (data->map[l])
	{
		c = 0;
		while (data->map[l][c])
		{
			if (data->map[l][c] == ' ')
				data->map[l][c] = '1';
			c++;
		}
		l++;
	}
}

int	check_is_map_closed(int l, int c, t_data *data)
{
	while (data->map[l])
	{
		c = 0;
		data->prs.line = data->map[l];
		while (data->map[l][c])
		{
			if (is_in_str(data->map[l][c], "02WESN"))
			{
				if (c == 0 || c == data->map_w - 1 || l == 0
					|| l == data->map_h - 1)
					return (print_err_atline(
							"non wall character at the edge of map", c, data));
				if (data->map[l][c + 1] == ' ' || data->map[l + 1][c] == ' '
					|| data->map[l][c - 1] == ' ' || data->map[l - 1][c] == ' ')
					return (print_err_atline(
							"non wall character next to empty space", c, data));
			}
			c++;
		}
		data->prs.line_num++;
		l++;
	}
	map_replace_space_with_wall(data);
	return (parse_plns(data));
}
