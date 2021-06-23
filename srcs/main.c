#include "cub3d.h"

static int	init_vs(t_data *data)
{
	data->vs.ptr = mlx_new_image(data->mlx, data->w, data->h);
	if (format_img(&(data->vs), data->w, data->h))
		return (print_err("failed to allocate virtual screen"));
	if (data->w * data->h > MAX_PIX_NB)
	{
		data->is_scaled = 1;
		data->w /= 2;
		data->h /= 2;
	}
	if (calc_base_screen_rays(data))
		return (-1);
	return (0);
}

static int	init_mlx(t_data *data)
{
	if (data->w > 1 && data->w % 2)
		data->w--;
	if (data->h > 1 && data->h % 2)
		data->h--;
	if (data->w * data->h > MAX_PIX_NB)
	{
		if (data->w % 4)
			data->w += 2;
		if (data->h % 4)
			data->h += 2;
	}
	data->win = mlx_new_window(data->mlx, data->w, data->h, "Cub3D");
	if (data->win == NULL)
		return (print_err("failed to create window"));
	if (init_vs(data))
		return (-1);
	if (calc_minimap(data))
		return (-1);
	mlx_hook(data->win, KEY_PRESS, 0, key_pressed, data);
	mlx_hook(data->win, KEY_RELEASE, 0, key_released, data);
	mlx_hook(data->win, DESTROY_NOTIFY, 0, quit, data);
	mlx_loop_hook(data->mlx, update, data);
	return (0);
}

static int	init(int argc, char **argv, t_data *data)
{
	if (argc != 2)
		return (print_err("expected one argument"));
	if (init_data(argv[1], data))
		return (-1);
	if (check_ext(data->prs.file, ".cub", 1))
		return (print_err_fstr("expected extension '.cub' for file '%s'",
				data->prs.file));
	data->prs.fd = open(data->prs.file, O_RDONLY);
	if (data->prs.fd == -1)
		return (print_err_fstr("failed to open file '%s'", data->prs.file));
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (init(argc, argv, &data))
		return (0);
	if (parse_file(&data))
	{
		close(data.prs.fd);
		free_data(&data);
		return (0);
	}
	if (init_mlx(&data))
	{
		free_data(&data);
		return (0);
	}
	mlx_loop(data.mlx);
}
