#include "cub3d.h"

int	scene_elem(int selem, int flag, t_data *data)
{
	if (flag == FL_ADD)
	{
		if (data->selems & selem)
			return (print_err_atline("element defined before", 0, data));
		data->selems |= selem;
	}
	else if (flag == FL_CHECK_ALL)
	{
		if (data->selems != (SELEM_C | SELEM_EA | SELEM_F | SELEM_NO | SELEM_R
				| SELEM_SO | SELEM_WE))
		{
			if (data->prs.line[get_ni(data->prs.line, 0)] == '1')
				return (print_err_infile(
						"missing one or more element defnition", data));
			return (print_err_atline("unknown element definition", 0, data));
		}
		if (data->prs.line[get_ni(data->prs.line, 0)] != '1')
			return (print_err_atline("expected '1' character",
					get_ni(data->prs.line, 0), data));
	}
	return (0);
}
