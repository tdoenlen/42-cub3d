#include "cub3d.h"

int	print_err(char *msg)
{
	print_err_intro();
	printf("%s", msg);
	print_err_outro();
	return (-1);
}

int	print_err_fstr(char *msg, char *s)
{
	print_err_intro();
	printf(msg, s);
	print_err_outro();
	return (-1);
}

int	print_err_infile(char *msg, t_data *data)
{
	print_err_intro();
	printf("in file '%s': %s", data->prs.file, msg);
	print_err_outro();
	return (-1);
}

int	print_err_atline(char *msg, int i, t_data *data)
{
	print_err_intro();
	printf("line %d in file '%s': %s\n%s\n", data->prs.line_num,
		data->prs.file, msg, data->prs.line);
	while (i--)
		printf(" ");
	printf("^");
	print_err_outro();
	return (-1);
}
