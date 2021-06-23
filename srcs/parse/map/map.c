#include "cub3d.h"

static int	clean_map(t_data *data)
{
	int	i;

	data->prs.line_num -= data->map_h;
	while (data->map[data->map_h - 1][get_ni(data->map[data->map_h - 1], 0)]
		== '\0')
	{
		data->map = pop_str_tab(data->map);
		if (data->map == NULL)
			return (print_err("allocation failed while parsing map"));
		data->map_h--;
	}
	i = 0;
	while (data->map[i])
	{
		data->map[i] = set_str_len(data->map[i], data->map_w);
		if (data->map[i] == NULL)
			return (print_err("allocation failed while parsing map"));
		i++;
	}
	return (check_is_map_closed(0, 0, data));
}

static int	check_map_line_char(int i, t_data *data)
{
	if (is_in_str(data->prs.line[i], "NSWE"))
	{
		if (data->pos.x != -1.)
			return (print_err_atline("spawn defined before", i, data));
		data->pos.x = (double)i + 0.5;
		data->pos.y = (double)data->map_h + 0.5;
		if (data->prs.line[i] == 'N')
			data->za = 0.;
		else if (data->prs.line[i] == 'S')
			data->za = M_PI;
		else if (data->prs.line[i] == 'W')
			data->za = -M_PI_2;
		else if (data->prs.line[i] == 'E')
			data->za = M_PI_2;
	}
	else if (!is_in_str(data->prs.line[i], "01"))
		return (print_err_atline("expected a map character", i, data));
	return (0);
}

static int	check_map_line(t_data *data)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	while (data->prs.line[i])
	{
		if (data->prs.line[i] != ' ')
		{
			max = i;
			if (check_map_line_char(i, data))
				return (-1);
		}
		i++;
	}
	if (max + 1 > data->map_w)
		data->map_w = max + 1;
	data->map_h++;
	data->map = append_str_tab(data->map, data->prs.line);
	if (data->map == NULL)
		return (print_err("allocation failed while parsing map"));
	return (i);
}

int	parse_map(t_data *data)
{
	int	gnl_ret;

	gnl_ret = 1;
	while (gnl_ret == 0 || gnl_ret == 1)
	{
		if (check_map_line(data) == -1)
			return (-1);
		if (gnl_ret == 0)
			gnl_ret = 2;
		else
			gnl_ret = get_next_line(data->prs.fd, &(data->prs.line));
		data->prs.line_num++;
	}
	if (gnl_ret == -1)
		return (print_err_fstr("failed to read file '%s'",
				data->prs.file));
	if (data->pos.x == -1.)
		return (print_err_infile("missing spawn in map", data));
	return (clean_map(data));
}
