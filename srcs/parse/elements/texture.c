#include "cub3d.h"

static int	parse_ttr_xpm_or_png(int s_i, int is_xpm, t_img *ttr, t_data *data)
{
	int	i;

	i = s_i;
	while (data->prs.line[i] && data->prs.line[i] != ' ')
		i++;
	if (data->prs.line[i] == ' ')
		return (print_err_atline("expected end of line", i, data));
	if (is_xpm)
		ttr->ptr = mlx_xpm_file_to_image(data->mlx, data->prs.line + s_i,
				&(ttr->w), &(ttr->h));
	else
		ttr->ptr = mlx_png_file_to_image(data->mlx, data->prs.line + s_i,
				&(ttr->w), &(ttr->h));
	if (format_img(ttr, ttr->w, ttr->h))
		return (print_err_atline("failed to convert to image", s_i, data));
	return (0);
}

int	parse_ttr(int i, t_img *ttr, t_data *data)
{
	int	s_i;
	int	is_xpm;

	if (data->prs.line[i] == '\0')
		return (print_err_atline("expected space", i, data));
	s_i = get_ni(data->prs.line, i);
	if (data->prs.line[s_i] == '\0')
		return (print_err_atline("expected path to the texture", s_i, data));
	is_xpm = 1;
	i = check_ext(data->prs.line + s_i, ".xpm", 0);
	if (i)
	{
		is_xpm = 0;
		i = check_ext(data->prs.line + s_i, ".png", 0);
	}
	if (i)
		return (print_err_atline("expected extension '.xpm' or '.png' for file",
				i + s_i, data));
	if (parse_ttr_xpm_or_png(s_i, is_xpm, ttr, data))
		return (-1);
	printf("'%s' converted to image.\n", data->prs.line + s_i);
	return (1);
}
