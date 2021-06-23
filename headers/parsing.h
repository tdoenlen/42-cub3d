#ifndef PARSING_H
# define PARSING_H

# define BUFFER_SIZE 32

typedef struct s_gnl_data
{
	char	buf[BUFFER_SIZE + 1];
	int		i;
	int		n;
	int		fd;
}	t_gnl_data;

enum
{
	SELEM_UNKNW = 0,
	SELEM_R = 1 << 0,
	SELEM_NO = 1 << 1,
	SELEM_SO = 1 << 2,
	SELEM_EA = 1 << 3,
	SELEM_WE = 1 << 4,
	SELEM_F = 1 << 5,
	SELEM_C = 1 << 6,
};

enum
{
	FL_ADD,
	FL_CHECK_ALL
};

int	scene_elem(int selem, int flag, t_data *data);
int	parse_file(t_data *data);
int	parse_elems(t_data *data);
int	parse_res(int i, t_data *data);
int	parse_ttr(int i, t_img *ttr, t_data *data);
int	parse_clr(int i, unsigned int *clr, t_data *data);
int	parse_map(t_data *data);
int	check_is_map_closed(int l, int c, t_data *data);
int	parse_plns(t_data *data);

#endif
