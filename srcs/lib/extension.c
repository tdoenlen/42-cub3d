#include "cub3d.h"

int	check_ext(char *file, char *ext, char is_case_s)
{
	int	f_i;
	int	e_i;

	f_i = ft_strlen(file) - 1;
	e_i = ft_strlen(ext) - 1;
	while (f_i >= 0 && e_i >= 0
		&& ((to_upper(file[f_i]) == to_upper(ext[e_i]) && !is_case_s)
			|| (file[f_i] == ext[e_i] && is_case_s)))
	{
		f_i--;
		e_i--;
	}
	if (e_i >= 0)
	{
		while (f_i > 0 && file[f_i] != '.' && file[f_i] != '/')
			f_i--;
		if (f_i && file[f_i] == '.')
			return (f_i);
		return (ft_strlen(file));
	}
	return (0);
}
