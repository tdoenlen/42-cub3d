#include "cub3d.h"

static int	get_n_clrp_i(int i, t_data *data)
{
	while (data->prs.line[i] >= '0' && data->prs.line[i] <= '9')
		i++;
	i = get_ni(data->prs.line, i);
	if (data->prs.line[i] != ',')
		return (print_err_atline("expected comma", i, data));
	i++;
	return (get_ni(data->prs.line, i));
}

static int	parse_clr_param(int i, t_data *data)
{
	int	n;

	if (data->prs.line[i] < '0' || data->prs.line[i] > '9')
		return (print_err_atline("expected numeric value", i, data));
	n = ft_atoi(data->prs.line + i);
	if (n > 255 || n == -1)
		return (print_err_atline("value out of range [0-255]", i, data));
	return (n);
}

static int	last_check(int i, unsigned int *clr, t_data *data)
{
	while (data->prs.line[i] >= '0' && data->prs.line[i] <= '9')
		i++;
	if (data->prs.line[i])
		return (print_err_atline("expected end of line", i, data));
	printf("Registered color '%#.8X'.\n", *clr);
	return (1);
}

int	parse_clr(int i, unsigned int *clr, t_data *data)
{
	int	n;
	int	offset;

	if (data->prs.line[i] != ' ')
		return (print_err_atline("expected space", i, data));
	offset = 16;
	while (offset >= 0)
	{
		if (offset == 16)
			i = get_ni(data->prs.line, i);
		else
		{
			i = get_n_clrp_i(i, data);
			if (i == -1)
				return (-1);
		}
		n = parse_clr_param(i, data);
		if (n == -1)
			return (-1);
		*clr += (unsigned int)n << offset;
		offset -= 8;
	}
	return (last_check(i, clr, data));
}
