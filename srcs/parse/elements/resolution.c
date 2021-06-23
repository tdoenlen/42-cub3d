#include "cub3d.h"

static int	clamp_w_h(t_data *data)
{
	int	w;
	int	h;

	(void)mlx_get_screen_size(data->mlx, &w, &h);
	if (data->w > w || data->w == -1)
	{
		data->w = w;
		printf("Warning: width has been truncated (too big).\n");
	}
	if (data->h > h || data->h == -1)
	{
		data->h = h;
		printf("Warning: height has been truncated (too big).\n");
	}
	printf("Width: %d, height: %d.\n", data->w, data->h);
	return (1);
}

static int	parse_height(int i, t_data *data)
{
	if (data->prs.line[i] < '0' || data->prs.line[i] > '9')
		return (print_err_atline("expected height", i, data));
	data->h = ft_atoi(data->prs.line + i);
	if (data->h == 0)
		return (print_err_atline("height cannot be null", i, data));
	while (data->prs.line[i] >= '0' && data->prs.line[i] <= '9')
		i++;
	if (data->prs.line[i])
		return (print_err_atline("expected end of line", i, data));
	return (clamp_w_h(data));
}

int	parse_res(int i, t_data *data)
{
	if (data->prs.line[i] == '\0')
		return (print_err_atline("expected space", i, data));
	i = get_ni(data->prs.line, i);
	if (data->prs.line[i] < '0' || data->prs.line[i] > '9')
		return (print_err_atline("expected width", i, data));
	data->w = ft_atoi(data->prs.line + i);
	if (data->w == 0)
		return (print_err_atline("width cannot be null", i, data));
	while (data->prs.line[i] >= '0' && data->prs.line[i] <= '9')
		i++;
	if (data->prs.line[i] != ' ')
		return (print_err_atline("expected space", i, data));
	return (parse_height(get_ni(data->prs.line, i), data));
}
