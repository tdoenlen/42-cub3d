#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}	t_vect3;

typedef struct s_set_list
{
	void	*next;
	int		val;
}	t_lset;

typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		w;
	int		h;
	int		l;
	int		p;
	int		e;
}	t_img;

typedef struct s_plane
{
	t_vect3	n;
	double	d;
	double	tnum;
}	t_pln;

typedef struct s_cast_info
{
	t_vect3			inter;
	double			xt;
	double			yt;
	unsigned int	xclr;
	unsigned int	yclr;
	int				xdir;
	int				x_i;
	int				ydir;
	int				y_i;
}	t_cast_info;

typedef struct s_minimap
{
	t_img	img;
	double	plr_xsize;
	double	plr_ysize;
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;
	int		x_b;
	int		x_e;
	int		y_b;
	int		y_e;
}	t_mmap;

typedef struct s_planes
{
	t_pln	*we;
	t_pln	*ns;
}	t_plns;

typedef struct s_colors
{
	unsigned int	f;
	unsigned int	c;
}	t_clrs;

typedef struct s_textures
{
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
	t_img	s;
}	t_ttrs;

typedef struct s_parsing
{
	char	*file;
	char	*line;
	int		fd;
	int		line_num;
}	t_prs;

typedef struct s_data
{
	t_mmap	mmap;
	t_clrs	clrs;
	t_ttrs	ttrs;
	t_plns	plns;
	t_prs	prs;
	t_lset	*pk;
	t_vect3	*bsr;
	t_vect3	*sr;
	t_vect3	pos;
	t_img	vs;
	char	**map;
	void	*mlx;
	void	*win;
	double	delta;
	double	xa;
	double	ya;
	double	za;
	int		w;
	int		h;
	int		map_w;
	int		map_h;
	int		m_x;
	int		m_y;
	int		selems;
	char	is_scaled;
	char	is_m;
}	t_data;

int		init_data(char *file, t_data *data);
void	free_data(t_data *data);

int		lset_add(t_lset **lset, int new_val);
int		lset_rm(t_lset **lset, int rm_val);
int		lset_has_val(t_lset *lset, int val);
void	lset_clear(t_lset **lset);

t_vect3	*new_null_vect3(void);
t_vect3	*new_vect3(double x, double y, double z);
void	set_vect3(t_vect3 *vect3, double x, double y, double z);
void	vect3_mult_k(t_vect3 *vect3, double k);
t_vect3	get_vect3_rotate_z(t_vect3 *v, double c, double s);
t_vect3	get_vect3_rotate_x(t_vect3 *v, double c, double s);

#endif
