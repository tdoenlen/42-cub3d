#include "cub3d.h"

static int	is_id(char *id, t_data *data)
{
	int	i;

	i = 0;
	while (id[i] && data->prs.line[i] && id[i] == data->prs.line[i])
		i++;
	if (id[i] == '\0' && (data->prs.line[i] == ' '
			|| data->prs.line[i] == '\0'))
		return (1);
	return (0);
}

static int	check_id(t_data *data)
{
	if (is_id("R", data))
		return (SELEM_R);
	if (is_id("NO", data))
		return (SELEM_NO);
	if (is_id("SO", data))
		return (SELEM_SO);
	if (is_id("EA", data))
		return (SELEM_EA);
	if (is_id("WE", data))
		return (SELEM_WE);
	if (is_id("F", data))
		return (SELEM_F);
	if (is_id("C", data))
		return (SELEM_C);
	return (SELEM_UNKNW);
}

static int	parse_line(t_data *data)
{
	int	id;

	id = check_id(data);
	if (scene_elem(id, FL_ADD, data))
		return (-1);
	if (id == SELEM_R)
		return (parse_res(1, data));
	if (id == SELEM_NO)
		return (parse_ttr(2, &(data->ttrs.no), data));
	if (id == SELEM_SO)
		return (parse_ttr(2, &(data->ttrs.so), data));
	if (id == SELEM_EA)
		return (parse_ttr(2, &(data->ttrs.ea), data));
	if (id == SELEM_WE)
		return (parse_ttr(2, &(data->ttrs.we), data));
	if (id == SELEM_F)
		return (parse_clr(1, &(data->clrs.f), data));
	if (id == SELEM_C)
		return (parse_clr(1, &(data->clrs.c), data));
	return (0);
}

int	parse_elems(t_data *data)
{
	int	ret;

	ret = 1;
	while (ret == 1)
	{
		data->prs.line_num++;
		ret = get_next_line(data->prs.fd, &(data->prs.line));
		if (ret == -1)
			return (print_err_fstr("failed to read file '%s'", data->prs.file));
		if (ret == 0)
			return (print_err_infile(
					"no map found", data));
		if (*(data->prs.line) == '\0')
			data->prs.line = safe_free(data->prs.line);
		else
			ret = parse_line(data);
		if (ret == 1)
			data->prs.line = safe_free(data->prs.line);
	}
	if (ret == -1)
		return (-1);
	return (scene_elem(0, FL_CHECK_ALL, data));
}
